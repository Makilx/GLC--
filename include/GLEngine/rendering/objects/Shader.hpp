#pragma once 

#include <glad/glad.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GEUNIFORM_DECLARATION(type, action) void Uniform(std::string name, type value) {action;}

namespace GLEngine {
    class Shaders {
        public:
        Shaders();
        ~Shaders();

        void Use();
        
        GEUNIFORM_DECLARATION(float, glUniform1f(GetUniformLocation(name), value))
        GEUNIFORM_DECLARATION(glm::vec2, glUniform2f(GetUniformLocation(name), value.x, value.y))
        GEUNIFORM_DECLARATION(glm::vec3, glUniform3f(GetUniformLocation(name), value.x, value.y, value.z))
        GEUNIFORM_DECLARATION(glm::vec4, glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w))
        GEUNIFORM_DECLARATION(int, glUniform1i(GetUniformLocation(name), value))
        GEUNIFORM_DECLARATION(unsigned int, glUniform1ui(GetUniformLocation(name), value))
        GEUNIFORM_DECLARATION(glm::mat4, glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(value)))

        void AttachShader(GLenum type, std::string source);
        void AttachShaderFromFile(GLenum type, std::string filePath);

        private:
        int GetUniformLocation(std::string name) {
            if (uniformCache.find(name) != uniformCache.end()) {
                return uniformCache[name];
            }
            else {
                int location = glGetUniformLocation(id, name.c_str());
                uniformCache[name] = location;
                return location;
            }
        }

        unsigned int id;
        bool updated = false;
        std::unordered_map<std::string, int> uniformCache;
        std::vector<int> shaderCache;
    };
}