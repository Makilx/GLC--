#include <GLEngine/rendering/objects/Mesh.hpp>
using GLEngine::Mesh;

Mesh::Mesh() : vbo(GL_ARRAY_BUFFER), ibo(GL_ELEMENT_ARRAY_BUFFER) {
    vao.layout.Push<float>(3);
    vao.layout.Push<float>(2);
}

Mesh::Mesh(Vertex *vertices, size_t vBufferSize, unsigned int *indices, size_t iBufferSize) : vbo(GL_ARRAY_BUFFER), ibo(GL_ELEMENT_ARRAY_BUFFER) {
    vao.layout.Push<float>(3);
    vao.layout.Push<float>(2);

    SetVertices(vertices, vBufferSize);
    SetIndices(indices, iBufferSize);
}

// Methods

void Mesh::Draw(Shaders &shaders) {
    if (indicesCount == 0) return;

    vao.Bind();

    // Apply shaders
    shaders.Uniform("MeshPos", position);
    shaders.Uniform("MeshColor", color);
    shaders.Uniform("MeshTransparency", transparency);

    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
}

void Mesh::SetVertices(Vertex *vertices, size_t vBufferSize) {
    vbo.SetData(vertices, vBufferSize);
    vao.BindBuffer(vbo, true);
}

void Mesh::SetIndices(unsigned int *indices, size_t iBufferSize) {
    this->indicesCount = iBufferSize > 0 ? iBufferSize / sizeof(unsigned int) : 0;
    ibo.SetData(indices, iBufferSize);
    vao.BindBuffer(ibo, false);
}
