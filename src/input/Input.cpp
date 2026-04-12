#include <GLEngine/input/Input.hpp>
using GLEngine::Input;

glm::vec2               Input::lastPos = glm::vec2(0.0);
glm::vec2               Input::lockPos = glm::vec2(0.0);
glm::vec2               Input::pendingMouseDelta = glm::vec2(0.0);
glm::vec2               Input::warpTarget = glm::vec2(0.0);
glm::vec2               Input::mouseDelta = glm::vec2(0.0);
GLFWwindow*             Input::instance = NULL;
bool                    Input::ignoreWarpEvent = false;
GLEngine::Signal<GLEngine::MouseMoveEvent>  GLEngine::Input::OnMouseMove;
std::array<bool, GLFW_KEY_LAST + 1> Input::pressingKeys = {};
std::array<bool, GLFW_KEY_LAST + 1> Input::previousPressingKeys = {};
std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> Input::pressingMouseButtons = {};
std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> Input::previousPressingMouseButtons = {};
GLEngine::MouseState    Input::currentState = GLEngine::MouseState::Default;

void Input::Init(GLFWwindow *i) {
    instance = i;

    pressingKeys.fill(false);
    previousPressingKeys.fill(false);
    pressingMouseButtons.fill(false);
    previousPressingMouseButtons.fill(false);

    double x, y;
    glfwGetCursorPos(instance, &x, &y);
    lastPos = glm::vec2(x, y);
    lockPos = lastPos;

    // mouse event
    glfwSetMouseButtonCallback(instance, [](GLFWwindow *window, int button, int action, int mods){
        if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return;
        Input::pressingMouseButtons[button] = (action != GLFW_RELEASE);
    });

    glfwSetCursorPosCallback(instance, [](GLFWwindow *window, double x, double y) {
        glm::vec2 mousePos(x, y);

        if (Input::ignoreWarpEvent && glm::length(mousePos - Input::warpTarget) < 0.5f) {
            Input::lastPos = mousePos;
            Input::ignoreWarpEvent = false;
            return;
        }

        Input::ignoreWarpEvent = false;
        Input::pendingMouseDelta += mousePos - Input::lastPos;
        Input::lastPos = mousePos;
    });

    // key event
    glfwSetKeyCallback(instance, [](GLFWwindow *window, int key, int scanCode, int action, int mods){
        if (key < 0 || key > GLFW_KEY_LAST) return;
        Input::pressingKeys[key] = (action != GLFW_RELEASE);
    });
}

void Input::OnUpdate() {
    mouseDelta = pendingMouseDelta;
    pendingMouseDelta = glm::vec2(0.0f);

    // Event
    if (mouseDelta.x != 0.0f || mouseDelta.y != 0.0f) {
        MouseMoveEvent newEvent;
        newEvent.position = GetMousePos();
        OnMouseMove.Fire(newEvent);
    }

    if (currentState == MouseState::Locked || currentState == MouseState::LockedCenter) {
        if (currentState == MouseState::LockedCenter) {
            lockPos = glm::vec2(Window::GetInstance().GetSize()) / 2.0f;
        }

        lastPos = lockPos;
        warpTarget = lockPos;
        ignoreWarpEvent = true;
        glfwSetCursorPos(instance, lockPos.x, lockPos.y);
    }
}

glm::vec2 Input::GetMousePos() {
    double x, y;
    glfwGetCursorPos(instance, &x, &y);
    return glm::vec2(x, y);
}

glm::vec2 Input::GetMouseDelta() {
    return mouseDelta * -1.0f;
}

bool Input::GetMouseButton(MouseButton button) {
    return pressingMouseButtons[static_cast<int>(button)];
}

bool Input::IsMouseButtonDown(MouseButton button) {
    int index = static_cast<int>(button);
    return pressingMouseButtons[index] && !previousPressingMouseButtons[index];
}

bool Input::IsMouseButtonUp(MouseButton button) {
    int index = static_cast<int>(button);
    return !pressingMouseButtons[index] && previousPressingMouseButtons[index];
}

void Input::SetMouseState(MouseState state) {
    currentState = state;
    mouseDelta = glm::vec2(0.0f);
    pendingMouseDelta = glm::vec2(0.0f);
    ignoreWarpEvent = false;

    double x, y;
    glfwGetCursorPos(instance, &x, &y);
    lastPos = glm::vec2(x, y);
    lockPos = lastPos;

    if (state == MouseState::LockedCenter) {
        lockPos = glm::vec2(Window::GetInstance().GetSize()) / 2.0f;
        lastPos = lockPos;
        warpTarget = lockPos;
        ignoreWarpEvent = true;
        glfwSetInputMode(instance, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetCursorPos(instance, lockPos.x, lockPos.y);
        return;
    }

    if (state == MouseState::Locked) {
        warpTarget = lockPos;
        ignoreWarpEvent = true;
        glfwSetInputMode(instance, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetCursorPos(instance, lockPos.x, lockPos.y);
        return;
    }

    if (state == MouseState::Default || state == MouseState::Hidden || state == MouseState::Disabled) {
        glfwSetInputMode(instance, GLFW_CURSOR, static_cast<int>(state));
    }
}

bool Input::GetKey(Key key) {
    return pressingKeys[static_cast<int>(key)];
}

bool Input::IsKeyDown(Key key) {
    int index = static_cast<int>(key);
    return pressingKeys[index] && !previousPressingKeys[index];
}

bool Input::IsKeyUp(Key key) {
    int index = static_cast<int>(key);
    return !pressingKeys[index] && previousPressingKeys[index];
}
