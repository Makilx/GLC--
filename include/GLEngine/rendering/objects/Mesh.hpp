#pragma once

#include <GLEngine/rendering/objects/Buffer.hpp>
#include <GLEngine/rendering/objects/ArrayObject.hpp>
#include <GLEngine/rendering/objects/Shader.hpp>
#include <glm/glm.hpp>

namespace GLEngine {
    struct Vertex {
        float x;
        float y;
        float z;
        float texX;
        float texY;
    };

    class Mesh {
        public:
        Mesh();
        Mesh(Vertex *vertices, size_t vBufferSize, unsigned int *indices, size_t iBufferSize);

        void Draw(Shaders &shaders);

        void SetVertices(Vertex *vertices, size_t vBufferSize);
        void SetIndices(unsigned int *indices, size_t iBufferSize);

        glm::vec3 position = glm::vec3(0.0);
        glm::vec3 color = glm::vec3(1.0);
        float transparency = 1.0f;

        private:
        Buffer vbo;
        Buffer ibo;
        ArrayObject vao;
        unsigned int indicesCount = 0;
    };
}
