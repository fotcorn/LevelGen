#include <iostream>
#include <random>
#include <functional>

#include "Level.h"
#include "DrawLevel.h"
#include "AStar.h"

constexpr float LEVEL_FILLUP = 0.3;

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
            level.tiles[y][x].type = TileType::NONE;
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
