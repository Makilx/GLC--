#pragma once
#include <cmath>

namespace gle {
    struct Vec2 {
        float x, y;

        // Constructors
        constexpr Vec2() : x(0.0f), y(0.0f) {}
        constexpr Vec2(float x, float y) : x(x), y(y) {}

        // Unary
        constexpr Vec2 operator-() const { return {-x, -y}; }

        // Vector + Vector
        constexpr Vec2 operator+(const Vec2& v) const { return {x + v.x, y + v.y}; }
        constexpr Vec2 operator-(const Vec2& v) const { return {x - v.x, y - v.y}; }

        Vec2& operator+=(const Vec2& v) { x += v.x; y += v.y; return *this; }
        Vec2& operator-=(const Vec2& v) { x -= v.x; y -= v.y; return *this; }

        // Vector * scalar
        constexpr Vec2 operator*(float s) const { return {x * s, y * s}; }
        constexpr Vec2 operator/(float s) const { return {x / s, y / s}; }

        Vec2& operator*=(float s) { x *= s; y *= s; return *this; }
        Vec2& operator/=(float s) { x /= s; y /= s; return *this; }

        // Comparison
        constexpr bool operator==(const Vec2& v) const { return x == v.x && y == v.y; }
        constexpr bool operator!=(const Vec2& v) const { return !(*this == v); }

        // Length
        float Length() const { return std::sqrt(x * x + y * y); }
        float LengthSquared() const { return x * x + y * y; }

        // Normalize
        Vec2 Normalized() const {
            float len = Length();
            return len == 0.0f ? Vec2{} : (*this / len);
        }

        // Dot
        static float Dot(const Vec2& a, const Vec2& b) {
            return a.x * b.x + a.y * b.y;
        }

        // Lerp
        static Vec2 Lerp(const Vec2& a, const Vec2& b, float t) {
            return a + (b - a) * t;
        }
    };

    // Allow: scalar * vector
    inline constexpr Vec2 operator*(float s, const Vec2& v) {
        return v * s;
    }
}