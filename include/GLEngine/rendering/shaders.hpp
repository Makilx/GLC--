#pragma once

#include <GLEngine/pch.hpp>
#include <GLEngine/type/type.hpp>

namespace gle {
    enum class ShaderType {
        VertexShader = 0x8B31,
        FragmentShader = 0x8B30
    };

    class Shaders {
      public:
        ~Shaders();

        void Create();
        bool IsCreated() {
            return id != 0;
        }

        void Use();
        bool AttachShader(ShaderType type, std::string source);
        bool AttachShaderFromFile(ShaderType type, std::string filePath);
        bool Link();

        void SetUniform(std::string uniform, const float value);
        void SetUniform(std::string uniform, const Vec2 value);
        void SetUniform(std::string uniform, const Vec3 value);
        void SetUniform(std::string uniform, const Vec4 value);
        void SetUniform(std::string uniform, const Mat4 value);
        void SetUniform(std::string uniform, const CFrame value);
        void SetUniform(std::string uniform, const Color value);

      private:
        unsigned int id = 0;
        bool programUpdate = false;
        std::unordered_map<std::string, int> uniformCache;

        int GetUniformLocation(std::string uniform);
    };
}; // namespace gle