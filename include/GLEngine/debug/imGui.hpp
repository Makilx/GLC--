#pragma once

#include <GLEngine/pch.hpp>
#include <imgui.h>

namespace gle {
    class App;
    class ImGuiRenderer;

    class ImGuiDebugWindow {
      public:
        ~ImGuiDebugWindow();
        void Enable();
        void Disable();

      protected:
        virtual void OnRenderFrame() = 0;

      private:
        friend class ImGuiRenderer;
    }; // User will use it

    class ImGuiRenderer {
      private:
        static void Init();
        static void Terminate();
        static void Update();

        static void RegisterWindow(ImGuiDebugWindow *window);
        static void UnregisterWindow(ImGuiDebugWindow *window);
        static bool IsWindowRegistered(ImGuiDebugWindow *window);

        static std::vector<ImGuiDebugWindow *> windows;

        friend class ImGuiDebugWindow;
        friend class App;
    }; // A class only for the main runtime / user should access nothing from
       // this (with the solely exception of interface settings ofc)
} // namespace gle