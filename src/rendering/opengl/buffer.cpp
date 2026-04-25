#include <glad/glad.h>
#include <GLEngine/logger.hpp>
#include <GLEngine/rendering/opengl/buffer.hpp>
#include <GLEngine/rendering/renderer.hpp>
using namespace gle::opengl;

void gle::opengl::Buffer::Create() {
    if (IsCreated())
        return;
    if (!Renderer::Initialized()) {
        Logger::Log(R"(
            Failed to create buffer because
            the renderer is not initialized
            )",
                    LogType::Error);
        return;
    }
    glCreateBuffers(1, &id);
}

gle::opengl::Buffer::~Buffer() {
    if (!IsCreated())
        return;
    glDeleteBuffers(1, &id);
}

void gle::opengl::Buffer::Bind() {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to bind buffer because it wasnt
            created successfully
            )",
                    LogType::Warning);
        return;
    }
    glBindBuffer((GLenum)type, id);
}

void gle::opengl::Buffer::Unbind() {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to unbind buffer because it wasnt
            created successfully
            )",
                    LogType::Warning);
        return;
    }
    glBindBuffer((GLenum)type, 0);
}

void gle::opengl::Buffer::Data(void *data, size_t size) {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to set buffer data because it wasnt
            created successfully
            )",
                    LogType::Warning);
        return;
    }
    glNamedBufferData(id, size, data, (GLenum)usage);
}

void gle::opengl::Buffer::SubData(size_t offset, void *data, size_t size) {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to set buffer subdata because it wasnt
            created successfully
            )",
                    LogType::Warning);
        return;
    }
    glNamedBufferSubData(id, offset, size, data);
}

void gle::opengl::Buffer::SetType(BufferType type) {
    this->type = type;
}

void gle::opengl::Buffer::SetUsage(BufferUsage usage) {
    this->usage = usage;
}
