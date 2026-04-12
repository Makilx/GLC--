#include <GLEngine/rendering/objects/Texture.hpp>
using GLEngine::Texture;
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

Texture::Texture() {
    glGenTextures(1, &id);
}

Texture::Texture(std::string filePath) {
    glGenTextures(1, &id);
    Load(filePath);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Use(Shaders &shader, unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    Bind();

    shader.Uniform("Texture"+std::to_string(slot), slot);
}

void Texture::Load(std::string filePath) {
    stbi_set_flip_vertically_on_load(1);
    int width, height, channels;
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (!data) throw std::runtime_error("Failed to load texture at: "+filePath);

    GLenum imageType = channels > 3 ? GL_RGBA : GL_RGB;

    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, imageType, width, height, 0, imageType, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void Texture::SetImageType(TextureImageType type) {
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(type));	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(type));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(type));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(type));
}