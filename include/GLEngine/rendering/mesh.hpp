#pragma once

#include <GLEngine/rendering/opengl/buffer.hpp>
#include <GLEngine/rendering/opengl/vertexArray.hpp>
#include <GLEngine/rendering/shaders.hpp>
#include <GLEngine/type/type.hpp>

namespace gle {
    class Mesh {
      public:
        Mesh()
            : color("#fffff"), position(Vec3(0.0f, 0.0f, 0.0f)),
              vbo(opengl::BufferType::Array),
              ibo(opengl::BufferType::ElementArray) {
        }

        CFrame position;
        Color color;
        opengl::DataLayout layout;

        void Create();
        bool IsLoaded();

        void SetVertices(float *vertices, size_t bufferSize);
        void SetVertices(std::vector<float> vertices);
        void SetIndices(unsigned int *indices, size_t bufferSize);
        void SetIndices(std::vector<unsigned int> indices);
        void Draw(Shaders &shaders);

      private:
        opengl::Buffer vbo;
        opengl::Buffer ibo;
        opengl::VertexArray array;
        bool updateVertices = false;
        bool updateIndices = false;
        unsigned int indicesCount = 0;
    };
} // namespace gle
