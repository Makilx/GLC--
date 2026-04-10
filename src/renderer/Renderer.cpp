#include <GLEngine/rendering/Renderer.hpp>
#include <GLEngine/rendering/Window.hpp>
using GLEngine::Renderer;

// Initialize static variables
double Renderer::lastFrame = 0;
double Renderer::deltaTime = 0;

void Renderer::Init() {
    glEnable(GL_DEPTH_TEST);
}

double Renderer::GetTime() {
    return glfwGetTime();
}

double Renderer::GetDeltaTime() {
    return deltaTime;
}

void Renderer::SetBackground(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

// Methods

void Renderer::OnUpdate() {
    double currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
