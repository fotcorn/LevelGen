#include "Tile.h"
#include "Vec.h"

Rotation getRotation(const Vec2i& first, const Vec2i& second)
{
    if (first.x == second.x)
    {
        if (first.y > second.y)
        {
            return Rotation::None;
        }
        else
        {
            return Rotation::Clockwise180;
        }
    }
    else
    {
        if (first.x > second.x)
        {
            return Rotation::Clockwise270;
        }
        else
        {
            return Rotation::Clockwise90;
        }
    }
}
