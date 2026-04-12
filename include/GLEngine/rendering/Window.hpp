#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

namespace GLEngine {
    class Input;
    class Window {
        public:
        Window(int width, int height, std::string title);
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        static void Init(int width, int height, std::string title);
        static Window& GetInstance();

        void SwapBuffers();
        void SetFramerate(int framerate);
        void PollEvents();
        bool ShouldClose();
        glm::ivec2 GetSize();
        std::string GetTitle();
        void SetSize(glm::ivec2 size);
        void SetTitle(std::string title);
        void Close();

        private:
        static Window*  instance;
        GLFWwindow*     window = nullptr;
        std::string     name;

        friend class Input;
    };
}
