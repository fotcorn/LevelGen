#pragma once

#include <vector>
#include <string>

enum class EntryPath {
    Left,
    Right,
    Both,
};

enum class Path {
    None,
    Left,
    Right,
    Both,
};

enum class Rotation : int {
    None = 0,
    Clockwise90,
    Clockwise180,
    Clockwise270,
};

struct TileType {
    std::string name;
    Rotation rotation;
    EntryPath entryPath;
    Path left;
    Path bottom;
    Path right;
};

struct StartEndTile {
    std::string name;
    Rotation rotation;
    EntryPath startPath;
};
