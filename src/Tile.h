#pragma once

#include "Vec.h"

#include <vector>
#include <string>

enum class EntryPath {
    Left,
    Right,
};

enum class Path {
    None,
    Left,
    Right,
};

enum class Rotation : int {
    None = 0,
    Clockwise90,
    Clockwise180,
    Clockwise270,
};

enum class Direction : int {
    Up = 0,
    Right,
    Down,
    Left,
};

struct TileType {
    std::string name;
    Rotation rotation;
    EntryPath entryPath;
    Path left;
    Path down;
    Path right;
};

struct TileRef {
    TileType& tile;
    Direction direction;
    TileRef(TileType& tile, Direction direction) : tile(tile), direction(direction) {}
};

struct StartEndTile {
    std::string name;
    Rotation rotation;
    EntryPath startPath;
};

struct StartEndTileRef {
    StartEndTile& tile;
    Direction direction;
    StartEndTileRef(StartEndTile& tile, Direction direction) : tile(tile), direction(direction) {}
};

Direction getDirection(const Vec2i& first, const Vec2i& second);

EntryPath pathToEntryPath(Path);