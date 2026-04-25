#pragma once

#include <GLEngine/pch.hpp>

namespace gle {
    class App;

    class Renderer {
      public:
        static bool Initialized();

        static double GetTime();
        static double GetDeltaTime();

        static void SetBackgroundColor(float r, float g, float b, float a);

        static void SetVSYNC(bool enabled);
        static void SetFPSLimit(int fps);

      private:
        static int targetFramerate;
        static bool vsyncEnabled;
        static bool initialized;
        static double time;
        static double deltaTime;
        static double lastTime;

        static void Init();
        static void OnUpdate();

        friend class App;
    };
} // namespace gle