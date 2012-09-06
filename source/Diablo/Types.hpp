#pragma once
#include <Diablo/Root.hpp>

namespace Diablo
{
    /**/
    struct Coordinate
    {
        /**/
        enum Type
        {
            CENTER,
            LEFT,
            RIGHT,
        };

        /**/
        Double  x;
        Double  y;
        Type    type;

        /**/
        Coordinate( Double x_, Double y_, Type type_=CENTER ):
            x(x_),
            y(y_),
            type(type_)
        {
        }
    };
}
