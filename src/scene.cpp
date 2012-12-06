#include "scene.h"
#include "thread.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include "screen.hpp"

namespace rt
{
    Scene::Scene()
    {

    }

void Scene::renderArea(int x, int y, int width, int height, screen& s, bool oversampling = true)
{
    vector up = cam->getUp() ;
    Position centre = cam->getCentre();
    Position eye = cam->getEye();
    vector _up = up.unit();
    vector vcenter = vector(centre.getX() - eye.getX(), centre.getY() - eye.getY(), centre.getZ() - eye.getZ());
    vector right = vcenter.unit() ^ _up;
    // Rendering of the rectangle.
    for(int i = x; i < x + width; ++i)
    {
        for(int j = y; j < y + height; ++j)
        {
            double step = 0;
            double mL1 = 0;
            double mL2 = 0;
            double mL3 = 0;
            // Oversampling x 9
            if(oversampling)
                step = 0.25;

            for(double ho=i - step; ho <= i + step ; ho += step)
                for(double ve=j-step; ve <= j + step ; ve+=step)
                {
                    if(not oversampling)
                    {
                        ho++;//eviter une boucle infinie
                        ve++;
                    }
                    //  std::cout  << ho << " et " << ve << std::endl;
                    bool inter = false;
                    rt::Position p;
                    int o = 0;
                    vector v = (vcenter + (ho - s.width() / 2.0) * right + (ve - s.height() / 2.0) * _up).unit();
                    for(unsigned k = 0; k < objets.size(); k++)
                    {
                        if(objets[k]->intersect(eye, v))
                        {

                            rt::Position pos = objets[k]->getIntersection(eye, v);
                            if(inter)
                            {
                                if(eye.distance(pos) < eye.distance(p))
                                {
                                    p = pos;
                                    o = k;
                                }

                            }
                            else
                            {
                                inter = true;
                                p = pos;
                                o = k;
                            }
                        }
                    }

                    if(inter)
                    {
                        color temp = getIllumination(p, o, v, 1, 3);
                        mL1 += temp.get_red();
                        mL2 += temp.get_green();
                        mL3 += temp.get_blue();
                    }
                }
            if(oversampling)
            {
                mL1 /= 9.0;
                mL2 /= 9.0;
                mL3 /= 9.0;
            }

            s.set_pixel(i, j, color((int)mL1, (int)mL2, (int)mL3));
        }
    }
}

Scene::ThreadRender::ThreadRender(Scene& _sc,int _x, int _y, int _w, int _h, screen& _s) :
    sc(_sc),x(_x), y(_y), w(_w), h(_h), s(_s)
{

}
void Scene::ThreadRender::run()
{
    sc.renderArea(x,y,w,h,s);
}

void Scene::render(screen& s, int nbThreads)
{
    std::cout << "Rendering with " << nbThreads <<  " threads." << std::endl;

    std::cout << getNbObjects() << " objects. " << getNbLights() << " lights." << std::endl;
    // Most of the times, the number of procs is a power of 2.
    // Anyway, it's rarely a prime number (except 2...).
    int p2 = std::log(nbThreads) / std::log(2);//More efficient to detect the most significant bit
    int nb_w = 0; // Nombre de divisions de la largeur
    int nb_h = 0; // Nombre de morceaux en hauteur
    std::vector<ThreadRender*> threads(nbThreads);//A "pool" of threads
    //What is the longest side ?
    if(s.height() > s.width())
    {
        nb_w = std::pow(2, p2 / 2);
        nb_h = nbThreads / nb_w ;
    }
    else
    {
        nb_h = std::pow(2, p2 / 2);
        nb_w = nbThreads / nb_h ;
    }

    int w = s.width() / nb_w;
    int h = s.height() / nb_h;
    std::cout << "Parts are " << w << " x " << h << std::endl;
    std::cout << "There are " << nb_w << " parts in width and " << nb_h << " in height." << std::endl;

    time_t beginning = std::time(NULL);

    //int limit_w = w * (nb_w - 1); // useful when there are parts left by the divisions above.
    //int limit_h = h * (nb_h - 1 );
    int k = 0;
    //std::cout << "Number of simple parts : limit_w = " << limit_w << " and limit_h = " << limit_h << std::endl;
    for(int i = 0 ; i <  s.width(); i += w)
        for(int j = 0; j < s.height(); j += h)
        {
            std::cout << "Rendering of " << i << "," << j << " - " << w << "," << h << std::endl;
            threads[k] = new ThreadRender(*this,i,j,w,h,s);
            //renderArea(i,j,w ,h,s);
            k++;
        }
    for(k=0; k < nbThreads ; k++)
    {
        std::cout << "Launching thread n." << k + 1<< std::endl;
        threads[k]->exec();
    }
    s.update();
    for(k=0; k < nbThreads; k++)
    {
        threads[k]->join();
        s.update();//Probably useless
    }

    for(k=0; k < nbThreads; k++)
        delete threads[k];
    //Render the last parts (w,h + reminder of the devision)
    /*std::cout << "Rendering last parts" << std::endl;
    for(unsigned i = 0; i < limit_w ; i += w)
        renderArea(i, limit_h, w, s.height() - h, s);
    for(unsigned j=0; j < limit_h; j += h)
        renderArea(limit_w, j, s.width() - h, h, s);*/

    time_t end = std::time(NULL);
    std::cout << "End of rendering. Took " << end - beginning << " seconds." << std::endl;
}

void Scene::render(screen& s)
{
    render(s, Thread::nbCores());
}

void Scene::addMesh(Mesh* mesh)
{
    objets.push_back(mesh);
}

void Scene::addLight(Light* light)
{
    lights.push_back(light);
}

void Scene::setCamera(Camera* camera)
{
    cam = camera;
}

double Scene::getIlluminationR(const Position& p, int o, const vector& vect, int nbR, int nbTrans) const
{
	vector v = vect;
	vector tem = (-1 * v).unit();
	double phong = 0;
	double reflechie = 0;
	double transparenceLumiere = 0;
	double transparenceObjet = 0;

    for(int k = 0; k < lights.size(); ++k)
    {
    	phong += lights[k]->illuminateR(p, objets[o], tem);
    }

    phong = std::min(phong, 255.);

    vector reflection = (2 * (tem | objets[o]->getNormal(p, v)) * objets[o]->getNormal(p, v) - tem).unit();
	bool reflect = false;
	Position brill;
	int e = 0;

	for(unsigned k = 0; k < objets.size(); k++)
	{
		if(objets[k]->intersect(p, reflection))
		{

			rt::Position pos = objets[k]->getIntersection(p, reflection);
			if(k != o)
			{
				if(reflect)
				{
					if(p.distance(pos) < p.distance(brill))
					{

						brill = pos;
						e = k;
					}

				}
				else
				{
					reflect = true;
					brill = pos;
					e = k;
				}
			}
		}
	}
	if(nbR > 0)
	{

		if(reflect)
		{
	  			reflechie += getIlluminationR(brill, e, reflection, nbR - 1, nbTrans);

			reflechie = std::min(reflechie, 255.);
			//reflechie = 255;
		}
	}
	if(nbTrans > 0)
	{
				            printf("GoGo transparence:");
				            printf("%4f %4f %4f ", v.unit().x, v.unit().y, v.unit().z);
		double n1n2 = 1/(objets[o]->getTexture().getIndice());
		v = v.unit();
				            //printf("%f %f %f", p.getX(), p.getY(), p.getZ());
		vector normal = objets[o]->getNormal(p, v).unit();
		vector r =  (n1n2 * v - (- n1n2 * (v | normal) - std::sqrt(1 - n1n2 * n1n2 * (1 - (v | normal) *(v | normal)))) * normal).unit();
				            printf("%4f %4f %4f \n", r.x, r.y, r.z);
		Position transp(objets[o]->autreCote(p, r, p));
				            //printf(" %f %f %f\n", transp.getX(), transp.getY(), transp.getZ());

		vector normal2 = objets[o]->getNormal(transp, r).unit();
		tem = (n1n2 * r - (n1n2 * (r | normal2) - std::sqrt(1 - n1n2 * n1n2 * (1 - (r | normal2) *(r | normal2)))) * normal2).unit();
				            printf("%4f %4f %4f\n", tem.unit().x, tem.unit().y, tem.unit().z);

		if(objets[o]->getTexture().getTransparence() != 0)
		{
	  		for(int k = 0; k < lights.size(); ++k)
		  	{
		  		transparenceLumiere += lights[k]->illuminateR(transp, objets[o], tem);
			}

		  	transparenceLumiere = std::min(transparenceLumiere, 255.);
	   		bool brillance = false;

	   		for(unsigned k = 0; k < objets.size(); k++)
			{
				if(objets[k]->intersect(transp, tem))
	   	        {
					rt::Position pos = objets[k]->getIntersection(transp, tem);
					if(k != o)
					{
						if(brillance)
						{
						    if(transp.distance(pos) < transp.distance(brill))
						    {
						       brill = pos;
						       e = k;
						    }

						}
						else
						{
							brillance = true;
							brill = pos;
							e = k;
						}
					}

				}
			}
			if(brillance)
			{
			  		transparenceObjet += ((double) objets[e]->getTexture().getColorN().get_red() / ((double) 255)) * getIlluminationR(brill, e, tem, nbR, nbTrans - 1);
			  	transparenceObjet = std::min(transparenceObjet, 255.);
			}
		}
	}
	return std::min(((1 - objets[o]->getTexture().getTransparence()) * phong + (1 - objets[o]->getTexture().getTransparence()) * reflechie + objets[o]->getTexture().getTransparence() * transparenceLumiere + objets[o]->getTexture().getTransparence() * transparenceObjet), 255.);
}

double Scene::getIlluminationG(const Position& p, int o, const vector& vect, int nbR, int nbTrans) const
{
	vector v = vect;
	vector tem = (-1 * v).unit();
	double phong = 0;
	double transparenceLumiere = 0;
	double transparenceObjet = 0;
	double reflechie = 0;

    for(int k = 0; k < lights.size(); ++k)
    {
    	phong += lights[k]->illuminateG(p, objets[o], tem);
    }

    phong = std::min(phong, 255.);

    vector reflection = (2 * (tem | objets[o]->getNormal(p, v)) * objets[o]->getNormal(p, v) - tem).unit();
	bool reflect = false;
	Position brill;
	int e = 0;

	for(unsigned k = 0; k < objets.size(); k++)
	{
		if(objets[k]->intersect(p, reflection))
		{

			rt::Position pos = objets[k]->getIntersection(p, reflection);
			if(k != o)
			{
				if(reflect)
				{
					if(p.distance(pos) < p.distance(brill))
					{

						brill = pos;
						e = k;
					}

				}
				else
				{
					reflect = true;
					brill = pos;
					e = k;
				}
			}
		}
	}
	if(nbR > 0)
	{

		if(reflect)
		{
	  			reflechie += getIlluminationG(brill, e, reflection, nbR - 1, nbTrans);
			reflechie = std::min(reflechie, 255.);
		}
	}
	if(nbTrans > 0)
	{
				            //printf("GoGo transparence:");
				            //printf("%4f %4f %4f ", v.unit().x, v.unit().y, v.unit().z);
		double n1n2 = 1/(objets[o]->getTexture().getIndice());
		v = v.unit();
				            //printf("%f %f %f", p.getX(), p.getY(), p.getZ());
		vector normal = objets[o]->getNormal(p, v).unit();
		vector r =  (n1n2 * v - (- n1n2 * (v | normal) - std::sqrt(1 - n1n2 * n1n2 * (1 - (v | normal) *(v | normal)))) * normal).unit();
				            //printf("%4f %4f %4f \n", r.x, r.y, r.z);
		Position transp(objets[o]->autreCote(p, r, p));
				            //printf(" %f %f %f\n", transp.getX(), transp.getY(), transp.getZ());
				            //Position transp(objets[o]->autreCote(p, v, p));
		vector normal2 = objets[o]->getNormal(transp, r).unit();
		tem = (n1n2 * r - (n1n2 * (r | normal2) - std::sqrt(1 - n1n2 * n1n2 * (1 - (r | normal2) *(r | normal2)))) * normal2).unit();
				            //printf("%4f %4f %4f\n", tem.unit().x, tem.unit().y, tem.unit().z);

		if(objets[o]->getTexture().getTransparence() != 0)
		{
	  		for(int k = 0; k < lights.size(); ++k)
		  	{
		  		transparenceLumiere += lights[k]->illuminateG(transp, objets[o], tem);
			}

		  	transparenceLumiere = std::min(transparenceLumiere, 255.);
	   		bool brillance = false;

	   		for(unsigned k = 0; k < objets.size(); k++)
			{
				if(objets[k]->intersect(transp, tem))
	   	        {
					rt::Position pos = objets[k]->getIntersection(transp, tem);
					if(k != o)
					{
						if(brillance)
						{
						    if(transp.distance(pos) < transp.distance(brill))
						    {
						       brill = pos;
						       e = k;
						    }

						}
						else
						{
							brillance = true;
							brill = pos;
							e = k;
						}
					}

				}
			}
			if(brillance)
			{
			  		transparenceObjet += ((double) objets[e]->getTexture().getColorN().get_green() / ((double) 255)) * getIlluminationG(brill, e, tem, nbR, nbTrans - 1);
			  	transparenceObjet = std::min(transparenceObjet, 255.);
			}
		}
	}
	return std::min(((1 - objets[o]->getTexture().getTransparence()) * phong + (1 - objets[o]->getTexture().getTransparence()) * reflechie + objets[o]->getTexture().getTransparence() * transparenceLumiere + objets[o]->getTexture().getTransparence() * transparenceObjet), 255.);
}

double Scene::getIlluminationB(const Position& p, int o, const vector& vect, int nbR, int nbTrans) const
{
	//printf("entrée %d %d\n", nbR, nbTrans);
	//printf("vision: %f %f %f\n", vect.x, vect.y, vect.z);
	vector v = vect;
	vector tem = (-1 * v).unit();
	double phong = 0;
	double transparenceLumiere = 0;
	double transparenceObjet = 0;
	double reflechie = 0;

    for(int k = 0; k < lights.size(); ++k)
    {
    	phong += lights[k]->illuminateB(p, objets[o], tem);
    }

    phong = std::min(phong, 255.);

    vector reflection = (2 * (tem | objets[o]->getNormal(p, v)) * objets[o]->getNormal(p, v) - tem).unit();
	bool reflect = false;
	Position brill;
	int e = 0;

	for(unsigned k = 0; k < objets.size(); k++)
	{
		if(objets[k]->intersect(p, reflection))
		{

			rt::Position pos = objets[k]->getIntersection(p, reflection);
			if(k != o)
			{
				if(reflect)
				{
					if(p.distance(pos) < p.distance(brill))
					{

						brill = pos;
						e = k;
					}

				}
				else
				{
					reflect = true;
					brill = pos;
					e = k;
				}
			}
		}
	}
	if(nbR > 0)
	{

		if(reflect)
		{
	  		reflechie += getIlluminationB(brill, e, reflection, nbR - 1, nbTrans);

			reflechie = std::min(reflechie, 255.);
		}
	}
	if(nbTrans > 0)
	{
				            //printf("GoGo transparence:");
				            //printf("%4f %4f %4f ", v.unit().x, v.unit().y, v.unit().z);
		double n1n2 = 1/(objets[o]->getTexture().getIndice());
		v = v.unit();
				            //printf("%f %f %f", p.getX(), p.getY(), p.getZ());
		vector normal = objets[o]->getNormal(p, v).unit();
		vector r =  (n1n2 * v - (- n1n2 * (v | normal) - std::sqrt(1 - n1n2 * n1n2 * (1 - (v | normal) *(v | normal)))) * normal).unit();
	//	printf("r: %f %f %f %d %d\n", r.x,r.y,r.z,nbR, nbTrans);
				            //printf("%4f %4f %4f \n", r.x, r.y, r.z);
		Position transp(objets[o]->autreCote(p, r, p));
				            //printf(" %f %f %f\n", transp.getX(), transp.getY(), transp.getZ());
				            //Position transp(objets[o]->autreCote(p, v, p));
		vector normal2 = objets[o]->getNormal(transp, r).unit();
		tem = (n1n2 * r - (n1n2 * (r | normal2) - std::sqrt(1 - n1n2 * n1n2 * (1 - (r | normal2) *(r | normal2)))) * normal2).unit();
				            //printf("%4f %4f %4f\n", tem.unit().x, tem.unit().y, tem.unit().z);
//		printf("transmission: %f %f %f %d %d\n", tem.x,tem.y,tem.z, nbR, nbTrans);
		if(objets[o]->getTexture().getTransparence() != 0)
		{
	  		for(int k = 0; k < lights.size(); ++k)
		  	{
		  		transparenceLumiere += lights[k]->illuminateB(transp, objets[o], tem);
			}

		  	transparenceLumiere = std::min(transparenceLumiere, 255.);
	   		bool brillance = false;

	   		for(unsigned k = 0; k < objets.size(); k++)
			{
				if(objets[k]->intersect(transp, tem))
	   	        {
					rt::Position pos = objets[k]->getIntersection(transp, tem);
					if(k != o)
					{
						if(brillance)
						{
						    if(transp.distance(pos) < transp.distance(brill))
						    {
						       brill = pos;
						       e = k;
						    }

						}
						else
						{
							brillance = true;
							brill = pos;
							e = k;
						}
					}

				}
			}
			if(brillance)
			{
				//printf("Brillance sur %d %d\n", e, o);
		  		transparenceObjet += ((double) objets[e]->getTexture().getColorN().get_blue() / ((double) 255)) * getIlluminationB(brill, e, tem, nbR, nbTrans - 1); //changer les coefficiants !!!!!
//			  		printf("%f %d %d\n", getIlluminationB(brill, e, transp.vectTo(brill).unit(), nbR, nbTrans - 1), nbR, nbTrans);
			  	transparenceObjet = std::min(transparenceObjet, 255.);
			  	//transparenceObjet = objets[e]->getTexture().getColorN().get_green();
			}
		}
	}
	return std::min(((1 - objets[o]->getTexture().getTransparence()) * phong + (1 - objets[o]->getTexture().getTransparence()) * reflechie + objets[o]->getTexture().getTransparence() * transparenceLumiere + objets[o]->getTexture().getTransparence() * transparenceObjet), 255.);
}

}
