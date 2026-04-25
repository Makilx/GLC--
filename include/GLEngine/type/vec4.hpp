#pragma once
#include <cmath>

namespace gle {
    struct Vec4 {
        float x, y, z, w;

        // Constructors
        constexpr Vec4() : x(0), y(0), z(0), w(0) {}
        constexpr Vec4(float x, float y, float z, float w)
            : x(x), y(y), z(z), w(w) {}

        // Unary
        constexpr Vec4 operator-() const { return {-x, -y, -z, -w}; }

        // Vector + Vector
        constexpr Vec4 operator+(const Vec4 &v) const {
            return {x + v.x, y + v.y, z + v.z, w + v.w};
        }
        constexpr Vec4 operator-(const Vec4 &v) const {
            return {x - v.x, y - v.y, z - v.z, w - v.w};
        }

        Vec4 &operator+=(const Vec4 &v) {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return *this;
        }
        Vec4 &operator-=(const Vec4 &v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return *this;
        }

        // Vector * scalar
        constexpr Vec4 operator*(float s) const {
            return {x * s, y * s, z * s, w * s};
        }
        constexpr Vec4 operator/(float s) const {
            return {x / s, y / s, z / s, w / s};
        }

        Vec4 &operator*=(float s) {
            x *= s;
            y *= s;
            z *= s;
            w *= s;
            return *this;
        }
        Vec4 &operator/=(float s) {
            x /= s;
            y /= s;
            z /= s;
            w /= s;
            return *this;
        }

        // Comparison
        constexpr bool operator==(const Vec4 &v) const {
            return x == v.x && y == v.y && z == v.z && w == v.w;
        }
        constexpr bool operator!=(const Vec4 &v) const { return !(*this == v); }

        // Dot
        static constexpr float Dot(const Vec4 &a, const Vec4 &b) {
            return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
        }

        // Lerp
        static constexpr Vec4 Lerp(const Vec4 &a, const Vec4 &b, float t) {
            return a + (b - a) * t;
        }
    };

    // scalar * vector
    inline constexpr Vec4 operator*(float s, const Vec4 &v) {
        return v * s;
    }
}