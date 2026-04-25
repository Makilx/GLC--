#include <GLEngine/engine.hpp>

void gle::App::Run() {
    // Initialize all
    Window::Init();
    Renderer::Init();

    Window &instance = Window::GetInstance();

    // Custom init
    OnStart();

    // Runtime
    while (!instance.ShouldClose()) {
        instance.PollEvents();
        Renderer::OnUpdate();

        OnUpdate(Renderer::GetDeltaTime());

        instance.SwapBuffers();
    }

    // End
    OnEnd();
}