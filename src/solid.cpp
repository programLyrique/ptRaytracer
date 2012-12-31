#include "solid.h"

namespace rt
{
    Solid::Solid()
    {
        //ctor
    }

    Solid::Solid(Texture texture) : t(texture)
    {

    }

    vector Solid::getNormal(const Point& p, const vector& v) const
    {
        vector n = normal(p, v);
        return t.getBumpmap().normal(p, n);
    }
}
