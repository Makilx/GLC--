#pragma once

#include <GLEngine/rendering/Window.hpp>
#include <GLEngine/rendering/objects/Shader.hpp>
#include <glm/glm.hpp>

namespace GLEngine {
    class Camera {
        public:
        void Use(Shaders &shader) {
            // Get window size
            glm::ivec2 size = Window::GetInstance().GetSize();

            // Math
            glm::mat4 view(1.0f);
            glm::mat4 proj(1.0);

            // A view matrix is the inverse of the camera transform.
            view = glm::rotate(view, glm::radians(-rotation.x), glm::vec3(1, 0, 0));
            view = glm::rotate(view, glm::radians(-rotation.y), glm::vec3(0, 1, 0));
            view = glm::rotate(view, glm::radians(-rotation.z), glm::vec3(0, 0, 1));
            view = glm::translate(view, -position);
            
            if (orthoCamera)
                proj = glm::ortho(0.0f, (float)size.x, (float)size.y, 0.0f, 0.1f, 100.0f);
            else
                proj = glm::perspective(glm::radians(fieldOfView), ((float)size.x/(float)size.y), 0.1f, 100.0f);

            shader.Uniform("Camera", proj * view);
        }

        glm::vec3 position  = glm::vec3(0.0);
        glm::vec3 rotation  = glm::vec3(0.0);
        glm::vec3 up        = glm::vec3(0.0, 1.0, 0.0);
        float fieldOfView   = 90.0f;
        bool orthoCamera    = false;
    };
}
