#pragma once

#include <glad/glad.h>
#include <GLEngine/rendering/objects/Buffer.hpp>
#include <vector>

namespace GLEngine {
    struct ArrayLayoutElement {
        int count;
        GLenum type;
        bool normalized;
    };

    class ArrayLayout {
        public:
        void Apply() {
            size_t offset = 0;

            for (size_t i = 0; i < elements.size(); i++) {
                ArrayLayoutElement &element = elements[i];
                glVertexAttribPointer(i, element.count, element.type, element.normalized, stride, (const void*)offset);
                glEnableVertexAttribArray(i);
                offset += GetTypeSize(element.type) * element.count;
            }
        }

        template<typename T>
        void Push(int count, bool normalized = false);

        private:
        std::vector<ArrayLayoutElement> elements;
        size_t stride = 0;

        size_t GetTypeSize(GLenum element) {
            switch (element) {
                case GL_FLOAT: return sizeof(GLfloat);
                case GL_INT: return sizeof(GLint);
                case GL_UNSIGNED_INT: return sizeof(GLuint);
            }
            return 0;
        }
    };

    class ArrayObject {
        public:
        ArrayObject();
        ~ArrayObject();

        void Bind();
        void Unbind();
        void BindBuffer(Buffer &buffer, bool applyLayout = true);

        ArrayLayout layout;

        private:
        unsigned int id;
    };
}
