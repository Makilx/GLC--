#pragma once

#include <GLEngine/type/mat4.hpp>
#include <GLEngine/type/quat.hpp>
#include <GLEngine/type/vec3.hpp>

namespace gle {
    struct CFrame {
        Vec3 position;
        Quat rotation;

        // Constructors
        constexpr CFrame() : position(), rotation() {
        }

        constexpr CFrame(const Vec3 &pos) : position(pos), rotation(){};

        constexpr CFrame(const Vec3 &pos, const Quat &rot)
            : position(pos), rotation(rot) {
        }

        // Identity frame
        static constexpr CFrame Identity() {
            return CFrame(Vec3(0, 0, 0), Quat::Identity());
        }

        // Direction vectors
        Vec3 Forward() const {
            return rotation * Vec3(0, 0, -1);
        }
        Vec3 Right() const {
            return rotation * Vec3(1, 0, 0);
        }
        Vec3 Up() const {
            return rotation * Vec3(0, 1, 0);
        }

        // Transform a point from local space to world space
        Vec3 TransformPoint(const Vec3 &point) const {
            return position + (rotation * point);
        }

        // Inverse frame (world -> local)
        CFrame Inverse() const {
            Quat invRot = rotation.Inverse();
            Vec3 invPos = invRot * (-position);
            return CFrame(invPos, invRot);
        }

        // Combine frames (parent * child)
        CFrame operator*(const CFrame &other) const {
            Vec3 newPos = TransformPoint(other.position);
            Quat newRot = rotation * other.rotation;
            return CFrame(newPos, newRot);
        }

        // Convert to matrix
        Mat4 ToMat4() const {
            Vec3 r = Right();
            Vec3 u = Up();
            Vec3 f = Forward();

            Mat4 m = Mat4::Identity();

            // Column 0 — Right
            m.data[0] = r.x;
            m.data[1] = r.y;
            m.data[2] = r.z;

            // Column 1 — Up
            m.data[4] = u.x;
            m.data[5] = u.y;
            m.data[6] = u.z;

            // Column 2 — -Forward (OpenGL camera convention)
            m.data[8] = -f.x;
            m.data[9] = -f.y;
            m.data[10] = -f.z;

            // Column 3 — Position
            m.data[12] = position.x;
            m.data[13] = position.y;
            m.data[14] = position.z;

            return m;
        }
    };
} // namespace gle