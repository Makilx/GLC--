#pragma once

#include <glad/glad.h>
#include <GLEngine/rendering/Window.hpp>

namespace GLEngine {
    class Window;
    class Renderer {
        public:
        static void Init();
        static void OnUpdate();
        
        static double GetTime();
        static double GetDeltaTime();
        static void SetBackground(float r, float g, float b, float a);

        private:
        static double lastFrame;
        static double deltaTime;

        friend class Window;
    };
}