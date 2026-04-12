#include <glad/glad.h>
#include <GLEngine/rendering/Renderer.hpp>
#include <GLEngine/rendering/Window.hpp>
#include <GLEngine/input/Input.hpp>
#include <stdexcept>
#include <sstream>
using GLEngine::Window;

// Define static member
Window* Window::instance = nullptr;

namespace {
    void GLFWErrorCallback(int code, const char* description) {
        (void) code;
        (void) description;
    }

    [[noreturn]] void Terminate(GLFWwindow* window, const std::string& error) {
        if (window) {
            glfwDestroyWindow(window);
        }

        glfwTerminate();
        throw std::runtime_error(error);
    }

    void ConfigureContextHints() {
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
}

Window::Window(int width, int height, std::string title) {
    glfwSetErrorCallback(GLFWErrorCallback);
    if (!glfwInit()) {
        const char* description = nullptr;
        glfwGetError(&description);
        throw std::runtime_error(description ? description : "Failed to initialize GLFW");
    }

    ConfigureContextHints();
    
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        const char* description = nullptr;
        glfwGetError(&description);

        std::ostringstream message;
        message << "Failed to create GLFW window";
        if (description) {
            message << ": " << description;
        }

        Terminate(window, message.str());
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    // Load glad
    if (!gladLoadGL()) {
        Terminate(window, "Failed to load glad");
    }

    // Viewport data
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);

    // Window settings
    glfwSwapInterval(1);

    // Window events
    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height){
        glViewport(0, 0, width, height);
    });

    // Load input
    Input::Init(window);
}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }

    glfwTerminate();
}

void Window::Init(int width, int height, std::string title) {
    if (instance) return;
    instance = new Window(width, height, title);
}

Window& Window::GetInstance() {
    if (!instance) {
        throw std::runtime_error("Window::Init must be called before Window::GetInstance");
    }

    return *instance;
}

// Methods

void Window::SwapBuffers() {
    if (!window) {
        throw std::runtime_error("Cannot swap buffers before creating a GLFW window");
    }

    if (glfwGetCurrentContext() != window) {
        glfwMakeContextCurrent(window);
    }

    glfwSwapBuffers(window);
}

void Window::SetFramerate(int framerate) {
    if (!window) {
        throw std::runtime_error("Cannot change swap interval before creating a GLFW window");
    }

    if (glfwGetCurrentContext() != window) {
        glfwMakeContextCurrent(window);
    }

    glfwSwapInterval(framerate > 0 ? 1 : 0);
}

void Window::PollEvents() {
    Input::previousPressingKeys = Input::pressingKeys;
    Input::previousPressingMouseButtons = Input::pressingMouseButtons;
    glfwPollEvents();
}

bool Window::ShouldClose() {
    if (!window) {
        return true;
    }

    return glfwWindowShouldClose(window);
}

glm::ivec2 Window::GetSize() {
    if (!window) {
        return glm::ivec2(0, 0);
    }

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return glm::ivec2(width, height);
}

std::string Window::GetTitle() {
    return std::string(glfwGetWindowTitle(window));
}

void Window::SetSize(glm::ivec2 size) {
    glfwSetWindowSize(window, size.x, size.y);
}

void Window::SetTitle(std::string title) {
    glfwSetWindowTitle(window, title.c_str());
}

void Window::Close() {
    glfwSetWindowShouldClose(window, 1);
}