#pragma once

#include <GLEngine/pch.hpp>
#include <GLEngine/type/ivec2.hpp>

struct GLFWwindow;

namespace gle {
    class App;
    class Input;

    class Window {
      public:
        Window();
        ~Window();

        static Window &GetInstance();

        std::string GetTitle();
        void SetTitle(std::string title);
        IVec2 GetSize();
        void SetSize(IVec2 size);
        void Close();

      private:
        static Window *currentInstance;
        GLFWwindow *window;
        IVec2 size;

        static void Init();
        void SwapBuffers();
        void PollEvents();
        bool ShouldClose();

        friend class App;
        friend class Input;
    };
} // namespace gle