#include <GLEngine/rendering/objects/Shader.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using GLEngine::Shaders;

Shaders::Shaders() {
    id = glCreateProgram();
}

Shaders::~Shaders() {
    glDeleteProgram(id);
}

// Methods

void Shaders::Use() {
    if (updated) {
        updated = false;
        glLinkProgram(id);

        int linked = 0;
        glGetProgramiv(id, GL_LINK_STATUS, &linked);
        if (!linked) {
            int logLength = 0;
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);

            std::string infoLog(logLength > 0 ? logLength : 1, '\0');
            glGetProgramInfoLog(id, logLength, nullptr, infoLog.data());
            throw std::runtime_error("Failed to link shader program: " + infoLog);
        }

        // Delete shader cache
        for (int shaderId : shaderCache) {
            glDeleteShader(shaderId);
        }

        shaderCache.clear();
    }

    glUseProgram(id);
}

void Shaders::AttachShader(GLenum type, std::string source) {
    unsigned int shaderId = glCreateShader(type);
    const char *temp = source.c_str();

    glShaderSource(shaderId, 1, &temp, NULL);
    glCompileShader(shaderId);

    int compiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        int logLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

        std::string infoLog(logLength > 0 ? logLength : 1, '\0');
        glGetShaderInfoLog(shaderId, logLength, nullptr, infoLog.data());
        glDeleteShader(shaderId);
        throw std::runtime_error("Failed to compile shader: " + infoLog);
    }

    glAttachShader(id, shaderId);
    shaderCache.push_back(shaderId);
    updated = true;
}

void Shaders::AttachShaderFromFile(GLenum type, std::string filePath) {
    std::ifstream stream(filePath);
    if (!stream.is_open()) throw std::runtime_error("Failed to load shader files at: "+filePath);
    
    std::stringstream stringStream;
    stringStream << stream.rdbuf();

    AttachShader(type, stringStream.str());
}
