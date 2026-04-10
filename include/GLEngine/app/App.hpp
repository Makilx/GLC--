#pragma once

#include <string>
#include <glm/glm.hpp>

namespace GLEngine {
    class App {
        public:
        void Run();

        virtual void OnStart()  {}
        virtual void OnUpdate(double deltaTime) {}
        virtual void OnEnd()    {}

        std::string  appName     = "App";
        glm::ivec2   windowSize  = glm::ivec2(500, 400);
    };
}