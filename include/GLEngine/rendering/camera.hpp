#pragma once

#include <GLEngine/rendering/shaders.hpp>
#include <GLEngine/rendering/window.hpp>
#include <GLEngine/type/type.hpp>

namespace gle {
    class Camera {
      public:
        CFrame position;
        float fieldOfView = 90;
        Range clipPlanes = Range(0.1f, 100.0f); // Far plane Near plane
        bool orthographic = false;

        void Use(Shaders &shaders) {
            // Get window size
            IVec2 windowSize = Window::GetInstance().GetSize();
            const float width =
                static_cast<float>(windowSize.x > 0 ? windowSize.x : 1);
            const float height =
                static_cast<float>(windowSize.y > 0 ? windowSize.y : 1);

            // Create matrices
            Mat4 projection;

            if (orthographic)
                projection = Mat4::Ortho(0.0f, width, height, 0.0f,
                                         clipPlanes.min, clipPlanes.max);
            else
                projection = Mat4::Perspective(gle::toRadians(fieldOfView),
                                               width / height, clipPlanes.min,
                                               clipPlanes.max);

            // Output
            const Mat4 view = position.Inverse().ToMat4();
            shaders.SetUniform("CameraProjection", projection * view);
        }
    };
} // namespace gle
