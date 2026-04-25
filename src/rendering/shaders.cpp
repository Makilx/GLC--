#include <glad/glad.h>
#include <GLEngine/logger.hpp>
#include <GLEngine/rendering/renderer.hpp>
#include <GLEngine/rendering/shaders.hpp>
#include <fstream>
#include <sstream>

void gle::Shaders::Create() {
    if (IsCreated())
        return;
    if (!Renderer::Initialized()) {
        Logger::Log(R"(
            Failed to create shader program because
            the renderer is not initialized
            )",
                    LogType::Error);
        return;
    }
    id = glCreateProgram();
}

gle::Shaders::~Shaders() {
    if (!IsCreated())
        return;
    glDeleteProgram(id);
}

void gle::Shaders::Use() {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to link shader program because it wasnt
            created successfully
            )",
                    LogType::Warning);
        return;
    }

    // Safe link
    Link();

    // Use
    glUseProgram(id);
}

bool gle::Shaders::AttachShader(ShaderType type, std::string source) {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to attach shader to program because the program wasnt
            created successfully
            )",
                    LogType::Warning);
        return false;
    }

    // Create shader
    unsigned int shader = glCreateShader((int)type);
    const char *temp = source.c_str();
    glShaderSource(shader, 1, &temp, NULL);
    glCompileShader(shader);

    // Debug shader
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        int logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        std::string log(logLength, '\0');
        glGetShaderInfoLog(shader, logLength, nullptr, log.data());

        Logger::Log("Shader compilation failed:" + log, LogType::Warning);
        glDeleteShader(shader);
        return false;
    }

    // Finish
    glAttachShader(id, shader);
    glDeleteShader(shader);
    programUpdate = true;

    return true;
}

bool gle::Shaders::AttachShaderFromFile(ShaderType type, std::string filePath) {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to attach shader to program because the program wasnt
            created successfully
            )",
                    LogType::Warning);
        return false;
    }

    std::ifstream stream(filePath);
    if (!stream.is_open()) {
        Logger::Log(R"(
            Failed to attach shader to program because it was given
            an invalid shader path. Invalid path: 
            )" + filePath,
                    LogType::Warning);
        return false;
    }

    // Read all the file data and compile it
    std::stringstream data;
    data << stream.rdbuf();
    return AttachShader(type, data.str());
}

bool gle::Shaders::Link() {
    if (!programUpdate)
        return true;

    glLinkProgram(id);

    int success = 0;
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (success == GL_FALSE) {
        int logLength = 0;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);

        std::string log(logLength, '\0');
        glGetProgramInfoLog(id, logLength, nullptr, log.data());

        Logger::Log("Program link failed: " + log, LogType::Warning);
        return false;
    }

    programUpdate = false;
    uniformCache.clear();

    return true;
}

void gle::Shaders::SetUniform(std::string uniform, const float value) {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to set uniform because the program wasnt
            created successfully
            )",
                    LogType::Warning);
        return;
    }

    Use();
    glUniform1f(GetUniformLocation(uniform), value);
}

void gle::Shaders::SetUniform(std::string uniform, const Vec2 value) {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to set uniform because the program wasnt
            created successfully
            )",
                    LogType::Warning);
        return;
    }

    Use();
    glUniform2f(GetUniformLocation(uniform), value.x, value.y);
}

void gle::Shaders::SetUniform(std::string uniform, const Vec3 value) {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to set uniform because the program wasnt
            created successfully
            )",
                    LogType::Warning);
        return;
    }

    Use();
    glUniform3f(GetUniformLocation(uniform), value.x, value.y, value.z);
}

void gle::Shaders::SetUniform(std::string uniform, const Vec4 value) {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to set uniform because the program wasnt
            created successfully
            )",
                    LogType::Warning);
        return;
    }

    Use();
    glUniform4f(GetUniformLocation(uniform), value.x, value.y, value.z,
                value.w);
}

void gle::Shaders::SetUniform(std::string uniform, const Mat4 value) {
    if (!IsCreated())
        Create();
    if (!IsCreated()) {
        Logger::Log(R"(
            Failed to set uniform because the program wasnt
            created successfully
            )",
                    LogType::Warning);
        return;
    }

    Use();
    glUniformMatrix4fv(GetUniformLocation(uniform), 1, GL_FALSE, value.data);
}

void gle::Shaders::SetUniform(std::string uniform, const CFrame value) {
    SetUniform(uniform, value.ToMat4());
}

void gle::Shaders::SetUniform(std::string uniform, const Color value) {
    SetUniform(uniform, Vec4(value.r, value.g, value.b, value.a));
}

int gle::Shaders::GetUniformLocation(std::string uniform) {
    if (uniformCache.find(uniform) != uniformCache.end()) {
        return uniformCache[uniform];
    } else {
        int location = glGetUniformLocation(id, uniform.c_str());
        uniformCache.insert({uniform, location});
        return location;
    }
}
