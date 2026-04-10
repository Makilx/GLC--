#pragma once

#include <glad/glad.h>
#include <GLEngine/rendering/objects/Shader.hpp>
#include <string>
#include <glm/glm.hpp>

namespace GLEngine {
    class Texture {
        public:
        Texture();
        Texture(std::string filePath);
        ~Texture();

        void Bind();
        void Unbind();
        void Use(Shaders &shader, unsigned int slot = 0);
        void Load(std::string filePath);
        glm::ivec2 GetSize() { return size; }

        private:
        unsigned int id;
        glm::ivec2 size;
    };
}