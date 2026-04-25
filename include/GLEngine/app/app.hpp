#pragma once

#include <GLEngine/pch.hpp>
#include <GLEngine/type/ivec2.hpp>

namespace gle {
    constexpr static std::string_view windowTitle = "App";
    constexpr static IVec2 windowSize(500, 400);

    class App {
      public:
        virtual ~App() = default;

        virtual void OnStart() {}
        virtual void OnUpdate(double deltaTime) {}
        virtual void OnEnd() {}

        void Run();
    };
} // namespace gle