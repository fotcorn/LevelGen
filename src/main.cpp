#include <iostream>
#include <random>
#include <functional>

#include "Level.h"
#include "DrawLevel.h"
#include "AStar.h"

constexpr float LEVEL_FILLUP = 0.3;

std::vector<StartEndTile> startEndTiles = {
    {"Start-Left", Rotation::None, EntryPath::Left},
    {"Start-Right", Rotation::None, EntryPath::Right},
};

std::vector<TileType> tileTypes = {
    {"S-Left", Rotation::None, EntryPath::Left, Path::None, Path::Right, Path::None},
    {"S-Right", Rotation::None, EntryPath::Right, Path::None, Path::Left, Path::None},

    {"I-Left", Rotation::None, EntryPath::Left, Path::None, Path::Left, Path::None},
    {"I-Left", Rotation::Clockwise180, EntryPath::Right, Path::None, Path::Right, Path::None},

    {"L-Small", Rotation::None, EntryPath::Right, Path::Left, Path::None, Path::None},
    {"L-Small", Rotation::Clockwise270, EntryPath::Left, Path::None, Path::None, Path::Right},

    {"L-Big", Rotation::None, EntryPath::Left, Path::Right, Path::None, Path::None},
    {"L-Big", Rotation::Clockwise270, EntryPath::Right, Path::None, Path::None, Path::Left},   
};

int main()
{
    Level level;

    // random setup
    std::random_device rd;
    std::mt19937 mt(rd());
    auto zeroOneDistribution = std::bind(std::uniform_real_distribution<>(0.0f, 1.0f), mt);

    // fill level up with some random blocks
    for (size_t y = 0; y < LEVEL_SIZE; y++)
    {
        for (size_t x = 0; x < LEVEL_SIZE; x++) {
            level.tiles[y][x].occupied = zeroOneDistribution() < LEVEL_FILLUP;
        }
    }

    // set start and choose a random goal
    level.start = {{LEVEL_SIZE / 2, 3}}; // center top
    level.dest = {{static_cast<int>(LEVEL_SIZE * zeroOneDistribution()), static_cast<int>(LEVEL_SIZE * 0.9f)}};
    level.tiles[level.start.x][level.start.y].occupied = false;
    level.tiles[level.dest.x][level.dest.y].occupied = false;

    AStar<Level, LEVEL_SIZE,LEVEL_SIZE> aStar(level);

    std::vector<Vec2i> path = aStar.aStar(level.start, level.dest);
    for (Vec2i& tile : path)
    {
        level.tiles[tile.x][tile.y].path = true;
    }

    ExportLevelToPng(level);
}
