#pragma once

#include "Vec.h"
#include "Tile.h"

#include <vector>
#include <memory>

struct Tile {
    // TODO: switch to enum
    bool occupied = false;
    bool path = false;
};

constexpr int LEVEL_SIZE = 20;

struct Level {
    Tile tiles[LEVEL_SIZE][LEVEL_SIZE];
    Vec2i start;
    Vec2i dest;
    std::unique_ptr<StartEndTileRef> startTile;
    std::unique_ptr<StartEndTileRef> endTile;

    bool isOccupied(int x, int y) const
    {
        return tiles[x][y].occupied;
    }
};
