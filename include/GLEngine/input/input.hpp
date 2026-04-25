#pragma once

#include <GLEngine/event/event.hpp>
#include <GLEngine/type/vec2.hpp>
#include <array>

namespace gle {
    class App;

    enum class Key {
        Unknown = -1,

        Space = 0x20,
        Apostrophe = 0x27, /* ' */
        Comma = 0x2C,      /* , */
        Minus = 0x2D,      /* - */
        Period = 0x2E,     /* . */
        Slash = 0x2F,      /* / */

        D0 = 0x30,
        D1 = 0x31,
        D2 = 0x32,
        D3 = 0x33,
        D4 = 0x34,
        D5 = 0x35,
        D6 = 0x36,
        D7 = 0x37,
        D8 = 0x38,
        D9 = 0x39,

        Semicolon = 0x3B, /* ; */
        Equal = 0x3D,     /* = */

        A = 0x41,
        B = 0x42,
        C = 0x43,
        D = 0x44,
        E = 0x45,
        F = 0x46,
        G = 0x47,
        H = 0x48,
        I = 0x49,
        J = 0x4A,
        K = 0x4B,
        L = 0x4C,
        M = 0x4D,
        N = 0x4E,
        O = 0x4F,
        P = 0x50,
        Q = 0x51,
        R = 0x52,
        S = 0x53,
        T = 0x54,
        U = 0x55,
        V = 0x56,
        W = 0x57,
        X = 0x58,
        Y = 0x59,
        Z = 0x5A,

        LeftBracket = 0x5B,  /* [ */
        Backslash = 0x5C,    /* \ */
        RightBracket = 0x5D, /* ] */
        GraveAccent = 0x60,  /* ` */

        World1 = 0xA1,
        World2 = 0xA2,

        Escape = 0x100,
        Enter = 0x101,
        Tab = 0x102,
        Backspace = 0x103,
        Insert = 0x104,
        Delete = 0x105,
        Right = 0x106,
        Left = 0x107,
        Down = 0x108,
        Up = 0x109,
        PageUp = 0x10A,
        PageDown = 0x10B,
        Home = 0x10C,
        End = 0x10D,
        CapsLock = 0x118,
        ScrollLock = 0x119,
        NumLock = 0x11A,
        PrintScreen = 0x11B,
        Pause = 0x11C,

        F1 = 0x122,
        F2 = 0x123,
        F3 = 0x124,
        F4 = 0x125,
        F5 = 0x126,
        F6 = 0x127,
        F7 = 0x128,
        F8 = 0x129,
        F9 = 0x12A,
        F10 = 0x12B,
        F11 = 0x12C,
        F12 = 0x12D,
        F13 = 0x12E,
        F14 = 0x12F,
        F15 = 0x130,
        F16 = 0x131,
        F17 = 0x132,
        F18 = 0x133,
        F19 = 0x134,
        F20 = 0x135,
        F21 = 0x136,
        F22 = 0x137,
        F23 = 0x138,
        F24 = 0x139,
        F25 = 0x13A,

        KP0 = 0x140,
        KP1 = 0x141,
        KP2 = 0x142,
        KP3 = 0x143,
        KP4 = 0x144,
        KP5 = 0x145,
        KP6 = 0x146,
        KP7 = 0x147,
        KP8 = 0x148,
        KP9 = 0x149,
        KPDecimal = 0x14A,
        KPDivide = 0x14B,
        KPMultiply = 0x14C,
        KPSubtract = 0x14D,
        KPAdd = 0x14E,
        KPEnter = 0x14F,
        KPEqual = 0x150,

        LeftShift = 0x154,
        LeftControl = 0x155,
        LeftAlt = 0x156,
        LeftSuper = 0x157,
        RightShift = 0x158,
        RightControl = 0x159,
        RightAlt = 0x15A,
        RightSuper = 0x15B,
        Menu = 0x15C
    };

    enum class MouseButton {
        Button1 = 0x0,
        Button2 = 0x1,
        Button3 = 0x2,
        Button4 = 0x3,
        Button5 = 0x4,
        Button6 = 0x5,
        Button7 = 0x6,
        Button8 = 0x7,

        Left = Button1,
        Right = Button2,
        Middle = Button3
    };

    enum class MouseBehavior {
        Default = 0,
        LockedCenter = 1,
        LockedCurrentPosition = 2,
    };

    enum class CursorVisibility {
        Default = 0,
        Invisible = 1
    };

    enum class CursorConstraint {
        Default = 0,
        Locked = 1,
    };

    enum class InputState {
        Down = 0,
        Pressing = 1,
        Releasing = 2
    };

    // Events
    struct MouseButtonStateEvent : public Event {
        MouseButton button;
        InputState state;
        Vec2 position;

        std::string ToString() override { return "MouseButtonStateEvent"; }
        EVENT_CLASS_TYPE(MouseButtonState);
    };

    struct MouseMoveEvent : public Event {
        Vec2 position;

        std::string ToString() override { return "MouseMoveEvent"; }
        EVENT_CLASS_TYPE(MouseMoved);
    };

    struct KeyStateEvent : public Event {
        Key key;
        InputState state;

        std::string ToString() override { return "KeyStateEvent"; }
        EVENT_CLASS_TYPE(KeyState);
    };

    struct MouseScrollEvent : public Event {
        Vec2 scroll;

        std::string ToString() override { return "MouseScrollEvent"; }
        EVENT_CLASS_TYPE(MouseScroll);
    };

    // Main
    class Input {
      public:
        static bool GetKey(Key key, InputState state);
        static bool GetMouseButton(MouseButton button, InputState state);

        static Vec2 GetMousePos();
        static Vec2 GetMouseDelta();
        static Vec2 GetMouseScroll();
        static void SetMouseBehavior(MouseBehavior behavior);
        static void SetCursorVisibility(CursorVisibility visibility);
        static void SetCursorConstraint(CursorConstraint constraint);

        static Signal<MouseButtonStateEvent> OnMouseStateChanged;
        static Signal<MouseMoveEvent> OnMouseMove;
        static Signal<KeyStateEvent> OnKeyStateChanged;
        static Signal<MouseScrollEvent> OnMouseScroll;
        
      private:
        static Vec2 mousePos;
        static Vec2 mouseDelta;
        static Vec2 lockedMousePos;
        static Vec2 lastMousePos;
        static std::array<bool, 349> pressingKeys;
        static std::array<bool, 349> previousPressingKeys;
        static std::array<bool, 8> pressingMouseButtons;
        static std::array<bool, 8> previousPressingMouseButtons;
        static MouseBehavior mouseBehavior;
        static CursorVisibility cursorVisibility;
        static CursorConstraint cursorConstraint;
        static Vec2 mouseScroll;

        static void Init();
        static void OnUpdate();

        friend class App;
    };
}; // namespace gle