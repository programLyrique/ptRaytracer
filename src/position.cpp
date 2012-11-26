#include "position.h"

namespace rt
{
    Position::Position(int _x, int _y, int _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }


    double Position::get_y() const
    {
        return y;
    }


    double Position::get_x() const
    {
        return x;
    }

    double Position::get_z() const
    {
        return z;
    }

    void Position::set_x(x)
    {
        Position::x = x;
    }

    void Position::set_y(y)
    {
        Position::y = y;
    }

    void Position::set_z(z)
    {
        Position::z = z;
    }


     Position::Position()
    {
        x = 0;
        y = 0;
        z = 0;
    }


}
