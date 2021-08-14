#pragma once

template <typename T>
struct Vec2 {
    T x;
    T y;
};

template <typename T>
struct Vec3 {
    T x;
    T y;
    T z;
};

struct Vec2i : public Vec2<int>{};
struct Vec2f : public Vec2<float>{};
struct Vec3i : public Vec3<int>{};
struct Vec3f : public Vec3<float>{};
