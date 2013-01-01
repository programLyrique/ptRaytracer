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
        const vector n = normal(p, v);
        const Bumpmap *bmap = t.getBumpmap();
        if(bmap == NULL)
        {
            return n;
        }
        else
        {
            return bmap->normal(p, n).unit();
        }
    }
}
