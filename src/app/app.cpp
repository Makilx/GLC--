#include <GLEngine/engine.hpp>

void gle::App::Run() {
    // Initialize all
    Window::Init();
    Input::Init();
    Renderer::Init();

    Window &instance = Window::GetInstance();

    // Custom init
    OnStart();

    // Runtime
    while (!instance.ShouldClose()) {
        Input::OnUpdate();
        instance.PollEvents();
        Renderer::OnUpdate();

        OnUpdate(Renderer::GetDeltaTime());

        instance.SwapBuffers();
    }

    // Terminate window
    Window::Terminate();

    // End
    OnEnd();
}
