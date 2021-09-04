#include "Tile.h"
#include "Vec.h"

#include <cassert>

Direction getDirection(const Vec2i& first, const Vec2i& second)
{
    if (first.x == second.x)
    {
        if (first.y > second.y)
        {
            return Direction::Up;
        }
        else
        {
            return Direction::Down;
        }
    }
    else
    {
        if (first.x > second.x)
        {
            return Direction::Left;
        }
        else
        {
            return Direction::Right;
        }
    }
}

EntryPath pathToEntryPath(Path path)
{
    switch (path)
    {
    case Path::Left:
        return EntryPath::Left;
    case Path::Right:
        return EntryPath::Right;
    default:
        assert(false);
    }
    assert(false);
}
