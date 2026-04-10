#include <GLEngine/rendering/objects/ArrayObject.hpp>
using GLEngine::ArrayObject;

#define AOPUSH_MACRO(type, glType) template<> void GLEngine::ArrayLayout::Push<type>(int count, bool normalized) { elements.push_back({count, glType, normalized}); stride += GetTypeSize(glType) * count; }

AOPUSH_MACRO(float, GL_FLOAT);
AOPUSH_MACRO(int, GL_INT);
AOPUSH_MACRO(unsigned int, GL_UNSIGNED_INT);

//-------------------//

ArrayObject::ArrayObject() {
    glGenVertexArrays(1, &id);
}

ArrayObject::~ArrayObject() {
    glDeleteVertexArrays(1, &id);
}

// Methods

void ArrayObject::Bind() {
    glBindVertexArray(id);
}

void ArrayObject::Unbind() {
    glBindVertexArray(0);
}

void ArrayObject::BindBuffer(Buffer &buffer, bool applyLayout) {
    Bind();
    buffer.Bind();

    if (applyLayout)
        layout.Apply();
}
