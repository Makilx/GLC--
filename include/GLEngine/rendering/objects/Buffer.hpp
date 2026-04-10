#pragma once

#include <glad/glad.h>

namespace GLEngine {
    class Buffer {
        public:
        Buffer(GLenum type, GLenum defaultUsage = GL_STATIC_DRAW);
        Buffer(GLenum type, void *data, size_t size, GLenum defaultUsage = GL_STATIC_DRAW);
        ~Buffer();

        void Bind();
        void Unbind();

        void SetData(void *data, size_t size);
        void SetData(void *data, size_t size, GLenum customUsage);
        void SetSubData(size_t offset, void *data, size_t size);

        private:
        unsigned int id;
        GLenum type;
        GLenum usage;
    };
}