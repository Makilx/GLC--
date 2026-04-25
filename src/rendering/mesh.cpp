#include <glad/glad.h>
#include <GLEngine/logger.hpp>
#include <GLEngine/rendering/mesh.hpp>

void gle::Mesh::Create() {
    vbo.Create();
    ibo.Create();
    array.Create();
}

bool gle::Mesh::IsLoaded() {
    return vbo.IsCreated() && ibo.IsCreated() && array.IsCreated();
}

void gle::Mesh::SetVertices(float *vertices, size_t bufferSize) {
    if (!IsLoaded())
        Create();
    if (!IsLoaded()) {
        Logger::Log("Failed to set mesh vertices because mesh wasnt properly "
                    "initialized",
                    LogType::Warning);
        return;
    }
    vbo.Data(vertices, bufferSize);
    updateVertices = true;
}

void gle::Mesh::SetVertices(std::vector<float> vertices) {
    if (!IsLoaded())
        Create();
    if (!IsLoaded()) {
        Logger::Log("Failed to set mesh vertices because mesh wasnt properly "
                    "initialized",
                    LogType::Warning);
        return;
    }
    vbo.Data(&vertices[0], sizeof(float) * vertices.size());
    updateVertices = true;
}

void gle::Mesh::SetIndices(unsigned int *indices, size_t bufferSize) {
    if (!IsLoaded())
        Create();
    if (!IsLoaded()) {
        Logger::Log("Failed to set mesh indices because mesh wasnt properly "
                    "initialized",
                    LogType::Warning);
        return;
    }
    ibo.Data(indices, bufferSize);
    indicesCount = bufferSize / sizeof(unsigned int);
    updateIndices = true;
}

void gle::Mesh::SetIndices(std::vector<unsigned int> indices) {
    if (!IsLoaded())
        Create();
    if (!IsLoaded()) {
        Logger::Log("Failed to set mesh indices because mesh wasnt properly "
                    "initialized",
                    LogType::Warning);
        return;
    }
    ibo.Data(&indices[0], sizeof(unsigned int) * indices.size());
    indicesCount = indices.size();
    updateIndices = true;
}

void gle::Mesh::Draw(Shaders &shaders) {
    if (!IsLoaded())
        Create();
    if (!IsLoaded()) {
        Logger::Log("Failed to draw mesh because mesh wasnt properly "
                    "initialized",
                    LogType::Warning);
        return;
    }

    // Check indices
    if (indicesCount == 0)
        return;

    // Bind mesh
    array.Bind();

    // Update mesh
    if (updateVertices || layout.updateLayout) {
        updateVertices = false;
        vbo.Bind();
        layout.Consume();
    }

    if (updateIndices) {
        updateIndices = false;
        ibo.Bind();
    }

    // Mesh uniforms
    shaders.SetUniform("MeshColor", color);
    shaders.SetUniform("MeshPosition", position);

    // Draw
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
}
