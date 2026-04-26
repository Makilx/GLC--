#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLEngine/app/app.hpp>
#include <GLEngine/logger.hpp>
#include <GLEngine/rendering/window.hpp>

// Static Data
gle::Window *gle::Window::currentInstance = NULL;

// Helpers
void TerminateError(GLFWwindow *window, std::string reason, int code) {
    if (window)
        glfwDestroyWindow(window);
    glfwTerminate();

    gle::Logger::LogCritical(reason, code);
}

// Main
gle::Window::Window() {
    Logger::Log("Loading window", LogType::Output);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::string title(windowTitle);
    window =
        glfwCreateWindow(windowSize.x, windowSize.y, title.c_str(), NULL, NULL);
    if (!window)
        TerminateError(window, "Failed to create a new window", 100);
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    int width = 0;
    int height = 0;
    glfwGetWindowSize(window, &width, &height);
    size = IVec2(width, height);

    if (!gladLoadGL())
        TerminateError(window, "Failed to load glad", 101);

    // Final settings and callbacks
    glfwSwapInterval(1);
    glViewport(0, 0, size.x, size.y);

    glfwSetWindowSizeCallback(
        window, [](GLFWwindow *window, int width, int height) {
            Window *instance = (Window *)glfwGetWindowUserPointer(window);
            instance->size = IVec2(width, height);
            glViewport(0, 0, width, height);
        });

    Logger::Log("Loaded window", LogType::Success);
}

void gle::Window::Terminate() {
    delete currentInstance;
}

gle::Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void gle::Window::Init() {
    if (currentInstance)
        return;
    currentInstance = new Window();
}

void gle::Window::SwapBuffers() {
    glfwSwapBuffers(window);
}

void gle::Window::PollEvents() {
    glfwPollEvents();
}

bool gle::Window::ShouldClose() {
    return glfwWindowShouldClose(window);
}

gle::Window &gle::Window::GetInstance() {
    return *currentInstance;
}

std::string gle::Window::GetTitle() {
    return glfwGetWindowTitle(window);
}

void gle::Window::SetTitle(std::string title) {
    glfwSetWindowTitle(window, title.c_str());
}

gle::IVec2 gle::Window::GetSize() {
    int width = 0;
    int height = 0;
    glfwGetWindowSize(window, &width, &height);
    size = IVec2(width, height);
    return size;
}

void gle::Window::SetSize(IVec2 size) {
    this->size = size;
    glfwSetWindowSize(window, size.x, size.y);
    glViewport(0, 0, size.x, size.y);
}

void gle::Window::Close() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}
