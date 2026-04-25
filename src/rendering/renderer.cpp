#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLEngine/logger.hpp>
#include <GLEngine/rendering/renderer.hpp>
#include <chrono>
#include <thread>

// Static Data
int gle::Renderer::targetFramerate = -1;
bool gle::Renderer::vsyncEnabled = true;
bool gle::Renderer::initialized = false;
double gle::Renderer::time = 0;
double gle::Renderer::deltaTime = 0;
double gle::Renderer::lastTime = 0;

// Helper
static void APIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id,
                                     GLenum severity, GLsizei,
                                     const GLchar *message, const void *) {
    using namespace gle;

    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;

    std::string src;
    switch (source) {
    case GL_DEBUG_SOURCE_API:
        src = "API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        src = "Window";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        src = "Shader";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        src = "3rdParty";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        src = "App";
        break;
    default:
        src = "Other";
        break;
    }

    std::string msg =
        "[OpenGL][" + src + "][id:" + std::to_string(id) + "] " + message;

    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        Logger::Log(msg, LogType::Error);
        break;

    case GL_DEBUG_SEVERITY_MEDIUM:
        Logger::Log(msg, LogType::Warning);
        break;

    case GL_DEBUG_SEVERITY_LOW:
        Logger::Log(msg, LogType::Comment);
        break;

    default:
        break;
    }
}

// Main
void gle::Renderer::Init() {
    Logger::Log("Initializing renderer", LogType::Output);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugCallback, nullptr);

    // Kill notification spam
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
                          GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

    initialized = true;
    Logger::Log("Renderer initialized", gle::LogType::Success);
}

void gle::Renderer::OnUpdate() {
    double frameStart = glfwGetTime();

    // --- Delta time calculation ---
    time = frameStart;
    deltaTime = time - lastTime;
    lastTime = time;

    // --- Rendering ---
    glClear(GL_COLOR_BUFFER_BIT);

    // --- Framerate cap ---
    if (targetFramerate != -1 && !vsyncEnabled) {
        double frameEnd = glfwGetTime();
        double frameTime = frameEnd - frameStart;

        double targetFrameTime = 1.0 / targetFramerate;

        if (frameTime < targetFrameTime) {
            double sleepTime = targetFrameTime - frameTime;

            std::this_thread::sleep_for(
                std::chrono::duration<double>(sleepTime));
        }
    }
}

bool gle::Renderer::Initialized() {
    return initialized;
}

double gle::Renderer::GetTime() {
    return time;
}

double gle::Renderer::GetDeltaTime() {
    return deltaTime;
}

void gle::Renderer::SetBackgroundColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void gle::Renderer::SetVSYNC(bool enabled) {
    glfwSwapInterval(enabled ? 1 : 0);
    vsyncEnabled = enabled;
}

void gle::Renderer::SetFPSLimit(int framerate) {
    targetFramerate = framerate;
}