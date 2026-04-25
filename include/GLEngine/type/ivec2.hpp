#pragma once

namespace gle {
    struct IVec2 {
        int x, y;

        // Constructors
        constexpr IVec2() : x(0), y(0) {}
        constexpr IVec2(int x, int y) : x(x), y(y) {}

        // Unary
        constexpr IVec2 operator-() const { return {-x, -y}; }

        // Vector + Vector
        constexpr IVec2 operator+(const IVec2 &v) const {
            return {x + v.x, y + v.y};
        }
        constexpr IVec2 operator-(const IVec2 &v) const {
            return {x - v.x, y - v.y};
        }

        IVec2 &operator+=(const IVec2 &v) {
            x += v.x;
            y += v.y;
            return *this;
        }
        IVec2 &operator-=(const IVec2 &v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        // Vector * scalar
        constexpr IVec2 operator*(int s) const { return {x * s, y * s}; }
        constexpr IVec2 operator/(int s) const { return {x / s, y / s}; }

        IVec2 &operator*=(int s) {
            x *= s;
            y *= s;
            return *this;
        }
        IVec2 &operator/=(int s) {
            x /= s;
            y /= s;
            return *this;
        }

        // Comparison
        constexpr bool operator==(const IVec2 &v) const {
            return x == v.x && y == v.y;
        }
        constexpr bool operator!=(const IVec2 &v) const {
            return !(*this == v);
        }

        // Dot
        static constexpr int Dot(const IVec2 &a, const IVec2 &b) {
            return a.x * b.x + a.y * b.y;
        }
    };

    // scalar * vector
    inline constexpr IVec2 operator*(int s, const IVec2 &v) {
        return v * s;
    }
}