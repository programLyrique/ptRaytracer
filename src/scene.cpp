#include "scene.h"

#include <cmath>
#include <iostream>

namespace rt
{
    Scene::Scene()
    {

    }

    void Scene::renderArea(int x, int y, int width, int height, screen& s)
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

				  bool inter = false;
				  rt::Position p;
				  int o = 0;
				  vector v = (vcenter + (i - s.width() / 2) * right + (j - s.height() / 2) * _up).unit();
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
				  	vector tem = (-1 * v).unit();
				  	double l1 = 0;
				  	double l2 = 0;
				  	double l3 = 0;

				  	for(int k = 0; k < lampes.size(); ++k)
				  	{
				  		l1 += lampes[k]->illuminateR(p, objets[o], tem);
				  		l2 += lampes[k]->illuminateG(p, objets[o], tem);
				  		l3 += lampes[k]->illuminateB(p, objets[o], tem);
				  	}

				  	l1 = std::min(l1, 255.);
				  	l2 = std::min(l2, 255.);
				  	l3 = std::min(l3, 255.);
				  	
				  	vector reflection = (2 * (tem | objets[o]->getNormal(p)) * objets[o]->getNormal(p) - tem).unit();
				  	bool reflect = false;
				  	Position brill;
				  	int e = 0;
				  	
				  	for(unsigned k = 0; k < objets.size(); k++)
		            {
						  if(objets[k]->intersect(p, reflection))
						  {

								rt::Position pos = objets[k]->getIntersection(p, reflection);
								if(reflect)
								{
				                    if(p.distance(pos) < p.distance(brill))
				                    {
				                    	if(k != o)
				                    	{
				                       		brill = pos;
				                       		e = k;
				                       	}
				                    }

								}
								else
								{
									if(o != k)
									{
										reflect = true;
										brill = pos;
										e = k;
									}
								}
		                   }
		              }
		              
		              	double n1 = 0;
				  		double n2 = 0;
				  		double n3 = 0;
				  		
						if(reflect)
						{
					  		for(int k = 0; k < lampes.size(); ++k)
						  	{
						  		n1 += lampes[k]->illuminateR(brill, objets[e], brill.vectTo(p).unit());
						  		n2 += lampes[k]->illuminateG(brill, objets[e], brill.vectTo(p).unit());
						  		n3 += lampes[k]->illuminateB(brill, objets[e], brill.vectTo(p).unit());
						  	}

						  	n1 = std::min(n1, 255.);
						  	n2 = std::min(n2, 255.);
						  	n3 = std::min(n3, 255.);
					  	}
					  	
		                if( (1./(objets[o]->getTexture().getIndice()) * (v.unit()^objets[o]->getNormal(p).unit()).norm()) > 1)
		                {
		                	printf("brix will be shit\n");
		                }
		                //printf("GoGo transparence: ");
		                //printf("%4f %4f %4f ", v.unit().x, v.unit().y, v.unit().z);
		                vector r = 1/(objets[o]->getTexture().getIndice()) * v.unit() - (std::sqrt(1 - (1/(objets[o]->getTexture().getIndice()) * (v.unit()^objets[o]->getNormal(p)).norm() * (1/(objets[o]->getTexture().getIndice()) * (v.unit()^objets[o]->getNormal(p)).norm()))) + 1/(objets[o]->getTexture().getIndice()) * (v.unit() | objets[o]->getNormal(p))) * objets[o]->getNormal(p);
		                //printf("%4f %4f %4f ", r.unit().x, r.unit().y, r.unit().z);
		                Position transp(objets[o]->autreCote(p, r, p));
		                //Position transp(objets[o]->autreCote(p, v, p));
		                //tem = v;
		                tem = 1/(objets[e]->getTexture().getIndice()) * r.unit() - (std::sqrt(1 - (1/(objets[e]->getTexture().getIndice()) * (r.unit()^objets[e]->getNormal(transp)).norm() * (1/(objets[e]->getTexture().getIndice()) * (r.unit()^objets[e]->getNormal(transp)).norm()))) + 1/(objets[e]->getTexture().getIndice()) * (r.unit() | objets[e]->getNormal(transp))) * objets[e]->getNormal(transp);
		                //printf("%4f %4f %4f\n", tem.unit().x, tem.unit().y, tem.unit().z);
				  		double m1 = 0;
				  		double m2 = 0;
				  		double m3 = 0;
						
						double o1 = 0;
						double o2 = 0;
						double o3 = 0;
						
						if(objets[o]->getTexture().getTransparence() != 0)
						{
						
					  		for(int k = 0; k < lampes.size(); ++k)
						  	{
						  		m1 += lampes[k]->illuminateR(transp, objets[o], tem);
						  		m2 += lampes[k]->illuminateG(transp, objets[o], tem);
						  		m3 += lampes[k]->illuminateB(transp, objets[o], tem);
						  	}

						  	m1 = std::min(m1, 255.);
						  	m2 = std::min(m2, 255.);
						  	m3 = std::min(m3, 255.);
		              
		              		bool brillance = false;
		              		
		              		for(unsigned k = 0; k < objets.size(); k++)
						    {
								  if(objets[k]->intersect(transp, tem))
								  {

										rt::Position pos = objets[k]->getIntersection(transp, tem);
										if(brillance)
										{
								            if(p.distance(pos) < p.distance(brill))
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
						     if(brillance)
							{
						  		for(int k = 0; k < lampes.size(); ++k)
							  	{
							  		o1 += lampes[k]->illuminateR(brill, objets[e], brill.vectTo(p).unit());
							  		o2 += lampes[k]->illuminateG(brill, objets[e], brill.vectTo(p).unit());
							  		o3 += lampes[k]->illuminateB(brill, objets[e], brill.vectTo(p).unit());
							  	}

							  	n1 = std::min(o1, 255.);
							  	n2 = std::min(o2, 255.);
							  	n3 = std::min(o3, 255.);
						  	}
		              	}

                    s.set_pixel(i, j, color((int)std::min((l1 + objets[o]->getTexture().getTransparence() * m1 + (1 - objets[o]->getTexture().getTransparence()) * n1 + objets[o]->getTexture().getTransparence() * o1), 255.), (int)std::min((l2 + objets[o]->getTexture().getTransparence() * m2 + (1 - objets[o]->getTexture().getTransparence()) * n2 + objets[o]->getTexture().getTransparence() * o2), 255.), (int)std::min((l3 + objets[o]->getTexture().getTransparence() * m3 + (1 - objets[o]->getTexture().getTransparence()) * n3 + objets[o]->getTexture().getTransparence() * o3), 255.)));
				  }

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
        // Most of the times, the number of procs is a power of 2.
        // Anyway, it's rarely a prime number (except 2...).
        int p2 = std::log(nbThreads) / std::log(2);//More efficient to detect the most significant bit
        int nb_w = 0; // Nombre de divisions de la largeur
        int nb_h = 0; // Nombre de morceaux en hauteur
        std::vector<ThreadRender*> threads(nbThreads);
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
        int limit_w = w * (nb_w - 1);
        int limit_h = h * (nb_h - 1 );
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
        for(k=0; k < nbThreads ;k++)
        {
            std::cout << "Launching thread n." << k + 1<< std::endl;
            threads[k]->exec();
        }
        s.update();
        for(k=0;k < nbThreads; k++)
        {
            threads[k]->join();
            s.update();//Probably useless
        }

        for(k=0; k < nbThreads;k++)
            delete threads[k];
        //Render the last parts (w,h + reminder of the devision)
        /*std::cout << "Rendering last parts" << std::endl;
        for(unsigned i = 0; i < limit_w ; i += w)
            renderArea(i, limit_h, w, s.height() - h, s);
        for(unsigned j=0; j < limit_h; j += h)
            renderArea(limit_w, j, s.width() - h, h, s);*/
        std::cout << "End of rendering" << std::endl;
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
		lampes.push_back(light);
    }

    void Scene::setCamera(Camera* camera)
    {
		cam = camera;
    }

}
