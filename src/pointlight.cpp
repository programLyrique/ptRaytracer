#include "pointlight.h"

namespace rt
{
    PointLight::PointLight(double x, double y, double z, color c, Scene* scene) : Light(c, scene), Point(x, y, z)
    {

    }

    double PointLight::illuminate(const Point& p, const Solid* m, const vector vision)
    {
        /** need to create a function intersect in scene so just do scene->existInter() */

        if(scene->existInterBetween(*this, p))
            return 0;

    	double reda = std::max(0.,
                        ((double) m->getTexture().getColorN().get_red() / ((double) 255))
                        * (m->getNormal(p, vision.unit()).unit() | p.vectTo(*this).unit()));
    	double redb = std::max(0.,
                        ((double) m->getTexture().getColorB().get_red() / ((double) 255))
                        * std::pow(vision.unit()
                                  | (2 * (m->getNormal(p, vision.unit()).unit()
                                         | p.vectTo(*this).unit()) * m->getNormal(p, vision.unit()).unit() - p.vectTo(*this).unit()).unit()
                            , m->getTexture().getBrillance()));
        double greena = std::max(0.,
                        ((double) m->getTexture().getColorN().get_green() / ((double) 255))
                        * (m->getNormal(p, vision.unit()).unit() | p.vectTo(*this).unit()));
    	double greenbb = std::max(0.,
                        ((double) m->getTexture().getColorB().get_green() / ((double) 255))
                        * std::pow(vision.unit()
                                  | (2 * (m->getNormal(p, vision.unit()).unit()
                                         | p.vectTo(*this).unit()) * m->getNormal(p, vision.unit()).unit() - p.vectTo(*this).unit()).unit()
                            , m->getTexture().getBrillance()));
        double greena = std::max(0.,
                        ((double) m->getTexture().getColorN().get_blue() / ((double) 255))
                        * (m->getNormal(p, vision.unit()).unit() | p.vectTo(*this).unit()));
    	double greenbb = std::max(0.,
                        ((double) m->getTexture().getColorB().get_blue() / ((double) 255))
                        * std::pow(vision.unit()
                                  | (2 * (m->getNormal(p, vision.unit()).unit()
                                         | p.vectTo(*this).unit()) * m->getNormal(p, vision.unit()).unit() - p.vectTo(*this).unit()).unit()
                            , m->getTexture().getBrillance()));
        return color(std::min(couleur.get_red() * (reda + redb), 255.),
                     std::min(couleur.get_green() * (greena + greenb), 255.),
                     std::min(couleur.get_red() * (bluea + blueb), 255.));

    }

}
