#pragma once
#include <cmath>

namespace gle {

    struct Mat4 {
        float data[16] = {0};

        static Mat4 Identity() {
            Mat4 m;
            m.data[0] = 1;
            m.data[5] = 1;
            m.data[10] = 1;
            m.data[15] = 1;
            return m;
        }

        static Mat4 Perspective(float fov, float aspect, float near,
                                float far) {
            Mat4 m{};

            float t = std::tan(fov * 0.5f);

            m.data[0] = 1.0f / (aspect * t);
            m.data[5] = 1.0f / t;
            m.data[10] = -(far + near) / (far - near);
            m.data[11] = -1.0f;
            m.data[14] = -(2.0f * far * near) / (far - near);

            return m;
        }

        static Mat4 Ortho(float left, float right, float bottom, float top,
                          float near, float far) {
            Mat4 m = Identity();

            m.data[0] = 2.0f / (right - left);
            m.data[5] = 2.0f / (top - bottom);
            m.data[10] = -2.0f / (far - near);

            m.data[12] = -(right + left) / (right - left);
            m.data[13] = -(top + bottom) / (top - bottom);
            m.data[14] = -(far + near) / (far - near);

            return m;
        }

        const float *Data() const {
            return data;
        }

        // ------------------------
        // MATRIX MULTIPLICATION
        // ------------------------
        Mat4 operator*(const Mat4 &o) const {
            Mat4 r{};

            for (int col = 0; col < 4; ++col) {
                for (int row = 0; row < 4; ++row) {
                    r.data[col * 4 + row] =
                        data[0 * 4 + row] * o.data[col * 4 + 0] +
                        data[1 * 4 + row] * o.data[col * 4 + 1] +
                        data[2 * 4 + row] * o.data[col * 4 + 2] +
                        data[3 * 4 + row] * o.data[col * 4 + 3];
                }
            }

            return r;
        }

        Mat4 &operator*=(const Mat4 &o) {
            *this = *this * o;
            return *this;
        }
    };

} // namespace gle
