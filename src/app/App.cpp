#include <GLEngine/Engine.hpp>
#include <GLEngine/app/App.hpp>
#include <iostream>
using GLEngine::App;

void App::Run() {
    // Initialize engine
    GLEngine::Window::Init(windowSize.x, windowSize.y, appName);
    GLEngine::Renderer::Init();
    GLEngine::Window &currentInstance = GLEngine::Window::GetInstance();

    OnStart();

    // On update engine
    while (!currentInstance.ShouldClose()) {
        // Update
        currentInstance.PollEvents();
        Input::OnUpdate();
        Renderer::OnUpdate();

        // Trigger on render function
        OnUpdate(GLEngine::Renderer::GetDeltaTime());

        currentInstance.SwapBuffers();
    }

    OnEnd();
}