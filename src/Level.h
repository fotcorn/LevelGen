#pragma once

#include "Vec.h"

#include <vector>

enum class TileType {
    NONE,
    START_LEFT,
    START_RIGHT,
    I_LEFT,
    BIG_L,
    SMALL_L,
    S_LEFT,
    S_RIGHT,
};

struct Tile {
    // TODO: switch to enum
    bool occupied = false;
    bool path = false;
    TileType type = TileType::NONE;
};

constexpr int LEVEL_SIZE = 20;

struct Level {
    Tile tiles[LEVEL_SIZE][LEVEL_SIZE];
    Vec2i start;
    Vec2i dest;

    bool isOccupied(int x, int y) const
    {
        return tiles[x][y].occupied;
    }
};
