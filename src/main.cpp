#include <iostream>
#include <random>
#include <functional>

#include "Level.h"
#include "DrawLevel.h"

constexpr float LEVEL_FILLUP = 0.1;

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
    level.startX = LEVEL_SIZE / 2;
    level.startY = 3; // almost at the top of the level
    level.goalX = LEVEL_SIZE * zeroOneDistribution();
    level.goalY = LEVEL_SIZE * 0.9f;

    ExportLevelToPng(level);
}
