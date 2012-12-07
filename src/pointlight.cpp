#include "pointlight.h"

namespace rt
{
    PointLight::PointLight(double x, double y, double z, color c, Scene* scene) : Light(c, scene), Point(x, y, z)
    {

    }

    color PointLight::illuminate(const Point& p, const Solid* m, const vector vision) const
    {
        if(scene->existInterBetween( *(static_cast<const Point*>(this)), p))
        {
            return color::BLACK;
        }
        
        color cN = m->getTexture().getColorN();
        color cB = m->getTexture().getColorB();
        
    	double reda = std::max(0.,
                        ((double) cN.get_red() / 255.)
                        * (m->getNormal(p, vision.unit()).unit() | p.vectTo(*this).unit()));
    	double redb = ((double) cB.get_red() / 255.)
                        * std::pow(std::max(0., vision.unit()
                                  | (2 * (m->getNormal(p, vision.unit()).unit()
                                         | p.vectTo(*this).unit()) * m->getNormal(p, vision.unit()) - p.vectTo(*this).unit()).unit())
                                  , m->getTexture().getBrillance());
        double greena = std::max(0.,
                        ((double) cN.get_green() / 255.)
                        * (m->getNormal(p, vision.unit()).unit() | p.vectTo(*this).unit()));
    	double greenb = ((double) cB.get_green() / 255.)
                        * std::pow(std::max(0., vision.unit()
                                  | (2 * (m->getNormal(p, vision.unit()).unit()
                                         | p.vectTo(*this).unit()) * m->getNormal(p, vision.unit()) - p.vectTo(*this).unit()).unit())
                                  , m->getTexture().getBrillance());
        double bluea = std::max(0.,
                        ((double) cN.get_blue() / 255.)
                        * (m->getNormal(p, vision.unit()).unit() | p.vectTo(*this).unit()));
    	double blueb = ((double) cB.get_blue() / 255.)
                        * std::pow(std::max(0., vision.unit()
                                  | (2 * (m->getNormal(p, vision.unit()).unit()
                                         | p.vectTo(*this).unit()) * m->getNormal(p, vision.unit()) - p.vectTo(*this).unit()).unit())
                                  , m->getTexture().getBrillance());
        return color((int) (std::min(couleur.get_red() * (reda + redb), 255.)),
                     (int) (std::min(couleur.get_green() * (greena + greenb), 255.)),
                     (int) (std::min(couleur.get_blue() * (bluea + blueb), 255.)));

    }

}
