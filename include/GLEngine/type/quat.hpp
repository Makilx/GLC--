#pragma once
#include <GLEngine/type/vec3.hpp>
#include <cmath>

namespace gle {
    struct Quat {
        float x, y, z, w;

        // Constructors
        constexpr Quat() : x(0), y(0), z(0), w(1) {}
        constexpr Quat(float x, float y, float z, float w)
            : x(x), y(y), z(z), w(w) {}

        // Identity
        static constexpr Quat Identity() { return Quat(0, 0, 0, 1); }

        // Length
        float Length() const {
            return std::sqrt(x * x + y * y + z * z + w * w);
        }

        // Normalize
        Quat Normalized() const {
            float len = Length();
            return len == 0.0f ? Quat()
                               : Quat(x / len, y / len, z / len, w / len);
        }

        // Inverse (for unit quats this is conjugate)
        Quat Inverse() const { return Quat(-x, -y, -z, w); }

        // Quaternion multiplication (rotation composition)
        constexpr Quat operator*(const Quat &q) const {
            return {w * q.x + x * q.w + y * q.z - z * q.y,
                    w * q.y - x * q.z + y * q.w + z * q.x,
                    w * q.z + x * q.y - y * q.x + z * q.w,
                    w * q.w - x * q.x - y * q.y - z * q.z};
        }

        // Rotate vector
        Vec3 operator*(const Vec3 &v) const {
            Vec3 qv(x, y, z);
            Vec3 t = 2.0f * Vec3::Cross(qv, v);
            return v + w * t + Vec3::Cross(qv, t);
        }

        // From axis-angle (radians)
        static Quat FromAxisAngle(const Vec3 &axis, float angleRad) {
            float half = angleRad * 0.5f;
            float s = std::sin(half);
            float c = std::cos(half);

            Vec3 na = axis.Normalized();
            return Quat(na.x * s, na.y * s, na.z * s, c);
        }

        // Dot
        static constexpr float Dot(const Quat &a, const Quat &b) {
            return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
        }

        // Lerp (good enough for most engine uses)
        static Quat Lerp(const Quat &a, const Quat &b, float t) {
            Quat result(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t,
                        a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t);
            return result.Normalized();
        }
    };
}