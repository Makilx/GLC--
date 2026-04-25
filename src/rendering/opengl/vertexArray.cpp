#include <glad/glad.h>
#include <GLEngine/logger.hpp>
#include <GLEngine/rendering/opengl/vertexArray.hpp>
#include <GLEngine/rendering/renderer.hpp>
using namespace gle::opengl;

template <>
void DataLayout::Push<float>(unsigned int count, bool normalized) {
    elements.push_back({count, sizeof(GLfloat), GL_FLOAT, normalized});
    stride += sizeof(GLfloat) * count;
    updateLayout = true;
}

template <>
void DataLayout::Push<int>(unsigned int count, bool normalized) {
    elements.push_back({count, sizeof(GLint), GL_INT, normalized});
    stride += sizeof(GLint) * count;
    updateLayout = true;
}

template <>
void DataLayout::Push<unsigned int>(unsigned int count, bool normalized) {
    elements.push_back({count, sizeof(GLuint), GL_UNSIGNED_INT, normalized});
    stride += sizeof(GLuint) * count;
    updateLayout = true;
}

void DataLayout::Consume() {
    size_t offset = 0;

    for (size_t i = 0; i < elements.size(); i++) {
        glVertexAttribPointer(i, elements[i].count, elements[i].type,
                              elements[i].normalized, stride,
                              (const void *)offset);
        glEnableVertexAttribArray(i);
        offset += elements[i].typeSize * elements[i].count;
    }

    updateLayout = false;
}

gle::opengl::VertexArray::~VertexArray() {
    if (!IsCreated())
        return;
    glDeleteVertexArrays(1, &id);
}

void gle::opengl::VertexArray::Create() {
    if (IsCreated())
        return;
    if (!Renderer::Initialized()) {
        Logger::Log(R"(
            Failed to create vertex array because
            the renderer is not initialized
            )",
                    LogType::Error);
        return;
    }
    glGenVertexArrays(1, &id);
}

void gle::opengl::VertexArray::Bind() {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to bind vertex array because it wasnt
            created successfully
            )",
                    LogType::Warning);
        return;
    }
    glBindVertexArray(id);
}

void gle::opengl::VertexArray::Unbind() {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to unbind vertex array because it wasnt
            created successfully
            )",
                    LogType::Warning);
        return;
    }
    glBindVertexArray(0);
}
