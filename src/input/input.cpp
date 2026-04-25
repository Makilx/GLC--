#include <GLFW/glfw3.h>
#include <GLEngine/input/input.hpp>
#include <GLEngine/logger.hpp>
#include <GLEngine/rendering/window.hpp>

// Static Members
gle::Signal<gle::MouseButtonStateEvent> OnMouseStateChanged;
gle::Signal<gle::MouseMoveEvent> OnMouseMove;
gle::Signal<gle::KeyStateEvent> OnKeyStateChanged;
gle::Signal<gle::MouseScrollEvent> OnMouseScroll;
gle::Vec2 gle::Input::mousePos = gle::Vec2(0.0, 0.0);
gle::Vec2 gle::Input::mouseDelta = gle::Vec2(0.0, 0.0);
gle::Vec2 gle::Input::lastMousePos = gle::Vec2(0.0, 0.0);
gle::MouseBehavior gle::Input::mouseBehavior = gle::MouseBehavior::Default;
gle::CursorVisibility gle::Input::cursorVisibility =
    gle::CursorVisibility::Default;
gle::CursorConstraint gle::Input::cursorConstraint =
    gle::CursorConstraint::Default;
gle::Vec2 gle::Input::lockedMousePos = gle::Vec2(0.0, 0.0);

// Main
void gle::Input::Init() {
    Logger::Log("Initializing input", LogType::Output);

    // Get window
    Window &instance = Window::GetInstance();

    // Connect mouse and keyboard events
    glfwSetMouseButtonCallback(
        instance.window,
        [](GLFWwindow *window, int button, int action, int mods) {
            bool isPressing = action != GLFW_RELEASE;
            pressingMouseButtons[button] = isPressing;

            MouseButtonStateEvent event;
            event.state = isPressing ? InputState::Down : InputState::Releasing;
            event.position = mousePos;
            event.button = (MouseButton)button;
            OnMouseStateChanged.Fire(event);
        });

    glfwSetCursorPosCallback(
        instance.window, [](GLFWwindow *window, double xPos, double yPos) {
            Vec2 newPos = {(float)xPos, (float)yPos};

            switch (mouseBehavior) {
            case MouseBehavior::Default: {
                mouseDelta = newPos - lastMousePos;
                lastMousePos = newPos;
                mousePos = newPos;
                break;
            }

            case MouseBehavior::LockedCenter: {
                int w, h;
                glfwGetWindowSize(window, &w, &h);
                Vec2 center = {(float)w * 0.5f, (float)h * 0.5f};

                mouseDelta = newPos - center;
                mousePos = center;

                glfwSetCursorPos(window, center.x, center.y);
                break;
            }

            case MouseBehavior::LockedCurrentPosition: {
                mouseDelta = newPos - lockedMousePos;
                mousePos = lockedMousePos;

                glfwSetCursorPos(window, lockedMousePos.x, lockedMousePos.y);
                break;
            }
            }

            MouseMoveEvent event;
            event.position = mousePos;
            OnMouseMove.Fire(event);
        });

    glfwSetScrollCallback(instance.window,
                          [](GLFWwindow *window, double ofX, double ofY) {
                              mouseScroll.x = ofX;
                              mouseScroll.y = ofY;

                              MouseScrollEvent event;
                              event.scroll = mouseScroll;
                              OnMouseScroll.Fire(event);
                          });

    glfwSetKeyCallback(instance.window, [](GLFWwindow *window, int key,
                                           int scanCode, int action, int mods) {
        bool isPressing = action != GLFW_RELEASE;
        pressingMouseButtons[key] = isPressing;

        KeyStateEvent event;
        event.state = isPressing ? InputState::Down : InputState::Releasing;
        event.key = (Key)key;
        OnKeyStateChanged.Fire(event);
    });

    Logger::Log("Input initialized", LogType::Success);
}

void gle::Input::OnUpdate() {
    // Key press logic
    previousPressingKeys = pressingKeys;
    previousPressingMouseButtons = pressingMouseButtons;

    // Reset mouse delta
    mouseDelta = Vec2(0.0, 0.0);
    mouseScroll = Vec2(0.0, 0.0);
}

bool gle::Input::GetKey(Key key, InputState state) {
    switch (state) {
    case InputState::Down:
        return !previousPressingKeys[(unsigned int)key] &&
               pressingKeys[(unsigned int)key];
    case InputState::Pressing:
        return pressingKeys[(unsigned int)key];
    case InputState::Releasing:
        return previousPressingKeys[(unsigned int)key] &&
               !pressingKeys[(unsigned int)key];
    }
    return false;
}

bool gle::Input::GetMouseButton(MouseButton button, InputState state) {
    switch (state) {
    case InputState::Down:
        return !previousPressingMouseButtons[(unsigned int)button] &&
               pressingMouseButtons[(unsigned int)button];
    case InputState::Pressing:
        return pressingMouseButtons[(unsigned int)button];
    case InputState::Releasing:
        return previousPressingMouseButtons[(unsigned int)button] &&
               !pressingMouseButtons[(unsigned int)button];
    }
    return false;
}

gle::Vec2 gle::Input::GetMousePos() {
    return mousePos;
}

gle::Vec2 gle::Input::GetMouseDelta() {
    return mouseDelta;
}

gle::Vec2 gle::Input::GetMouseScroll() {
    return mouseScroll;
}

void gle::Input::SetMouseBehavior(MouseBehavior behavior) {
    mouseBehavior = behavior;

    Window &instance = Window::GetInstance();
    GLFWwindow *window = instance.window;

    if (behavior == MouseBehavior::LockedCurrentPosition) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        lockedMousePos = {(float)x, (float)y};
    }

    if (behavior == MouseBehavior::LockedCenter) {
        int w, h;
        glfwGetWindowSize(window, &w, &h);
        glfwSetCursorPos(window, w * 0.5, h * 0.5);
    }

    lastMousePos = mousePos; // prevent huge delta on switch
}

void gle::Input::SetCursorVisibility(CursorVisibility visibility) {
    cursorVisibility = visibility;

    Window &instance = Window::GetInstance();
    glfwSetInputMode(instance.window, GLFW_CURSOR,
                     visibility == CursorVisibility::Invisible
                         ? GLFW_CURSOR_HIDDEN
                         : GLFW_CURSOR_NORMAL);
}

void gle::Input::SetCursorConstraint(CursorConstraint constraint) {
    cursorConstraint = constraint;

    Window &instance = Window::GetInstance();
    glfwSetInputMode(instance.window, GLFW_CURSOR,
                     constraint == CursorConstraint::Locked
                         ? GLFW_CURSOR_DISABLED
                         : GLFW_CURSOR_NORMAL);
}