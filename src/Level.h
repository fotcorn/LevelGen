#pragma once

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
    bool occupied = false;
    TileType type = TileType::NONE;
};

constexpr int LEVEL_SIZE = 20;

struct Level {
    Tile tiles[LEVEL_SIZE][LEVEL_SIZE];
    int startX;
    int startY;
    int goalX;
    int goalY;
};
