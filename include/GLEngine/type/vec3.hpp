#pragma once
#include <cmath>

namespace gle {
    struct Vec3 {
        float x, y, z;

        // Constructors
        constexpr Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
        constexpr Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

        // Unary
        constexpr Vec3 operator-() const { return {-x, -y, -z}; }

        // Vector + Vector
        constexpr Vec3 operator+(const Vec3 &v) const {
            return {x + v.x, y + v.y, z + v.z};
        }
        constexpr Vec3 operator-(const Vec3 &v) const {
            return {x - v.x, y - v.y, z - v.z};
        }

        Vec3 &operator+=(const Vec3 &v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        Vec3 &operator-=(const Vec3 &v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        // Vector * scalar
        constexpr Vec3 operator*(float s) const {
            return {x * s, y * s, z * s};
        }
        constexpr Vec3 operator/(float s) const {
            return {x / s, y / s, z / s};
        }

        Vec3 &operator*=(float s) {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }
        Vec3 &operator/=(float s) {
            x /= s;
            y /= s;
            z /= s;
            return *this;
        }

        // Comparison
        constexpr bool operator==(const Vec3 &v) const {
            return x == v.x && y == v.y && z == v.z;
        }
        constexpr bool operator!=(const Vec3 &v) const { return !(*this == v); }

        // Length
        float Length() const { return std::sqrt(x * x + y * y + z * z); }
        float LengthSquared() const { return x * x + y * y + z * z; }

        // Normalize
        Vec3 Normalized() const {
            float len = Length();
            return len == 0.0f ? Vec3{} : (*this / len);
        }

        // Dot
        static constexpr float Dot(const Vec3 &a, const Vec3 &b) {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }

        // Cross
        static constexpr Vec3 Cross(const Vec3 &a, const Vec3 &b) {
            return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x};
        }

        // Lerp
        static constexpr Vec3 Lerp(const Vec3 &a, const Vec3 &b, float t) {
            return a + (b - a) * t;
        }
    };

    // scalar * vector
    inline constexpr Vec3 operator*(float s, const Vec3 &v) {
        return v * s;
    }

} // namespace gle