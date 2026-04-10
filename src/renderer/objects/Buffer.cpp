#include <GLEngine/rendering/objects/Buffer.hpp>
using GLEngine::Buffer;

Buffer::Buffer(GLenum type, GLenum defaultUsage) {
    this->type = type;
    this->usage = defaultUsage;

    glGenBuffers(1, &id);
}

Buffer::Buffer(GLenum type, void *data, size_t size, GLenum defaultUsage) {
    this->type = type;
    this->usage = defaultUsage;

    glGenBuffers(1, &id);
    SetData(data, size);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &id);
}

// Methods

void Buffer::Bind() {
    glBindBuffer(type, id);
}

void Buffer::Unbind() {
    glBindBuffer(type, 0);
}

void Buffer::SetData(void *data, size_t size) {
    Bind();
    glBufferData(type, size, data, usage);
}

void Buffer::SetData(void *data, size_t size, GLenum usage) {
    this->usage = usage;
    Bind();
    glBufferData(type, size, data, usage);
}

void Buffer::SetSubData(size_t offset, void *data, size_t size) {
    Bind();
    glBufferSubData(type, offset, size, data);
}
