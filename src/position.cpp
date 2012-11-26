#include "position.h"

namespace rt
{
    Position::Position(int _x, int _y, int _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    double Position::getX()
    {
        return x;
    }

    double Position::getY()
    {
        return y;
    }

    double Position::getZ()
    {
        return z;
    }
}
