#include <iostream>
#include <random>
#include <functional>
#include <cassert>

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


int getRandomInt(std::mt19937& engine, int min, int max)
{
    return std::uniform_int_distribution<>(min, max)(engine);
}

struct TileSearchResult {
    EntryPath entryPath;
    TileType& tileType;
    TileSearchResult(EntryPath entryPath, TileType& tileType) : entryPath(entryPath), tileType(tileType) {}
};

TileSearchResult getNextTileType(std::mt19937& mt, Direction directionIn, Direction directionOut, EntryPath entryPath);

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

    // generate path through level
    AStar<Level, LEVEL_SIZE,LEVEL_SIZE> aStar(level);
    std::vector<Vec2i> path = aStar.aStar(level.start, level.dest);
    for (Vec2i& tile : path)
    {
        level.tiles[tile.x][tile.y].path = true;
    }

    int startIndex = getRandomInt(mt, 0, startEndTiles.size() - 1);
    
    Vec2i* firstTile = &path[0];
    Vec2i* secondTile = &path[1];
    
    Direction directionIn = getDirection(*firstTile, *secondTile);
    level.startTile = std::make_unique<StartEndTileRef>(startEndTiles[startIndex], directionIn);
    EntryPath tileExitPath = level.startTile->tile.startPath;
    firstTile = secondTile;

    for (std::size_t i = 2; i < path.size(); i++)
    {
        secondTile = &path[i];
        Direction directionOut = getDirection(*firstTile, *secondTile);
        TileSearchResult nextTile = getNextTileType(mt, directionIn, directionOut, tileExitPath);
        level.tiles[firstTile->x][firstTile->y].tile = std::make_unique<TileRef>(nextTile.tileType, directionIn);

        firstTile = secondTile;
        directionIn = directionOut;
        tileExitPath = nextTile.entryPath;
    }

    //ExportLevelToPng(level);
}



Direction getTileDirection(Direction directionIn, Direction directionOut)
{
    switch (directionIn)
    {
    case Direction::Right:
    {
        switch (directionOut)
        {
        case Direction::Right:
            return Direction::Down; // same direction is always down
        case Direction::Left:
            assert(false);  // invalid direction
        case Direction::Up:
            return Direction::Right;
        case Direction::Down:
            return Direction::Left;
        }
    }
    case Direction::Left:
    {
        switch (directionOut)
        {
        case Direction::Right:
            assert(false);  // invalid direction
        case Direction::Left:
            return Direction::Down;  // same direction is always down
        case Direction::Up:
            return Direction::Left;
        case Direction::Down:
            return Direction::Right;
        }
    }
    case Direction::Up:
    {
        switch (directionOut)
        {
        case Direction::Right:
            return Direction::Left;
        case Direction::Left:
            return Direction::Right;
        case Direction::Up:
            return Direction::Down;  // same direction is always down
        case Direction::Down:
            assert(false);  // invalid direction
        }
    }
    case Direction::Down:
    {
        switch (directionOut)
        {
        case Direction::Right:
            return Direction::Right;
        case Direction::Left:
            return Direction::Left;
        case Direction::Up:
            assert(false);  // invalid direction
        case Direction::Down:
            return Direction::Down;  // same direction is always down
        }
    }
    }
}




TileSearchResult getNextTileType(std::mt19937& mt, Direction directionIn, Direction directionOut, EntryPath entryPath)
{
    Direction tileDirection = getTileDirection(directionIn, directionOut);
    std::vector<TileSearchResult> matchingTileTypes;
    for (TileType& tileType : tileTypes)
    {
        if (tileType.entryPath != entryPath)
        {
            continue;
        }
        switch (tileDirection) {
            case Direction::Left:
                if (tileType.left != Path::None) {
                    matchingTileTypes.emplace_back(pathToEntryPath(tileType.left), tileType);
                }
                break;
            case Direction::Right:
                if (tileType.right != Path::None) {
                    matchingTileTypes.emplace_back(pathToEntryPath(tileType.right), tileType);
                }
                break;
            case Direction::Down:
                if (tileType.down != Path::None) {
                    matchingTileTypes.emplace_back(pathToEntryPath(tileType.down), tileType);
                }
                break;
            case Direction::Up:
                assert(false);
            // we are always coming in from the top, so Direction::Up can't happen
        }
    }

    const int index = getRandomInt(mt, 0, matchingTileTypes.size() - 1);
    return matchingTileTypes[index];
}
