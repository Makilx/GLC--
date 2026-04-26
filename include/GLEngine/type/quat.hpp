#pragma once
#include <GLEngine/type/vec3.hpp>
#include <cmath>

namespace gle {
    static double toRadians(double degrees) {
        return degrees * (M_PI / 180);
    }

    static double toDegrees(double radians) {
        return radians * (180 / M_PI);
    }

    struct Quat {
        float x, y, z, w;

        // Constructors
        constexpr Quat() : x(0), y(0), z(0), w(1) {
        }

        constexpr Quat(float x, float y, float z) : x(x), y(y), z(z), w(0) {
        }

        constexpr Quat(float x, float y, float z, float w)
            : x(x), y(y), z(z), w(w) {
        }

        static Quat FromEuler(float pitch, float yaw, float roll) {
            float cy = std::cos(yaw * 0.5f);
            float sy = std::sin(yaw * 0.5f);
            float cp = std::cos(pitch * 0.5f);
            float sp = std::sin(pitch * 0.5f);
            float cr = std::cos(roll * 0.5f);
            float sr = std::sin(roll * 0.5f);

            Quat q;
            q.w = cr * cp * cy + sr * sp * sy;
            q.x = sr * cp * cy - cr * sp * sy;
            q.y = cr * sp * cy + sr * cp * sy;
            q.z = cr * cp * sy - sr * sp * cy;

            return q;
        }

        static Quat FromEulerDegrees(const Vec3 &eulerDegrees) {
            Vec3 r(toRadians(eulerDegrees.x), toRadians(eulerDegrees.y),
                   toRadians(eulerDegrees.z));

            return FromEuler(r.x, r.y, r.z);
        }

        // Explicit camera-style rotation builder.
        // Yaw uses the engine's camera convention, then pitch and roll are
        // applied in that rotated space.
        static Quat FromYawPitchRoll(float yaw, float pitch, float roll = 0.0f) {
            const Quat yawRotation = FromAxisAngle(Vec3(0, -1, 0), yaw);
            const Quat pitchRotation = FromAxisAngle(Vec3(1, 0, 0), pitch);
            const Quat rollRotation = FromAxisAngle(Vec3(0, 0, 1), roll);

            return (yawRotation * pitchRotation * rollRotation).Normalized();
        }

        static Quat FromYawPitch(float yaw, float pitch) {
            return FromYawPitchRoll(yaw, pitch, 0.0f);
        }

        // Identity
        static constexpr Quat Identity() {
            return Quat(0, 0, 0, 1);
        }

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
        Quat Inverse() const {
            return Quat(-x, -y, -z, w);
        }

        // Quaternion multiplication (rotation composition)
        constexpr Quat operator*(const Quat &q) const {
            return {w * q.x + x * q.w + y * q.z - z * q.y,
                    w * q.y - x * q.z + y * q.w + z * q.x,
                    w * q.z + x * q.y - y * q.x + z * q.w,
                    w * q.w - x * q.x - y * q.y - z * q.z};
        }

        Quat &operator*=(const Quat &q) {
            float nx = w * q.x + x * q.w + y * q.z - z * q.y;
            float ny = w * q.y - x * q.z + y * q.w + z * q.x;
            float nz = w * q.z + x * q.y - y * q.x + z * q.w;
            float nw = w * q.w - x * q.x - y * q.y - z * q.z;

            x = nx;
            y = ny;
            z = nz;
            w = nw;

            return *this;
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
} // namespace gle
