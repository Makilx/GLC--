#pragma once

#include <functional>
#include "../pch.hpp"

#define EVENT_CLASS_TYPE(type)                                                 \
    static EventType GetStaticType() {                                         \
        return EventType::type;                                                \
    }                                                                          \
    virtual EventType GetType() const override {                               \
        return GetStaticType();                                                \
    }

namespace gle {
    enum class EventType {
        None = 0,
        KeyState,
        MouseMoved,
        MouseButtonState,
        MouseScroll
    };

    struct Event {
      public:
        bool IsHandled() {
            return handled;
        }
        void MarkHandled() {
            handled = true;
        }

        virtual std::string ToString() {
            return "Event";
        }
        virtual EventType GetType() const = 0;

      private:
        bool handled = false;
    };

    class EventDispatcher {
      public:
        EventDispatcher(Event &event) : e(event) {
        }

        template <typename EventType, typename Callback>
        bool Dispatch(Callback callback) {
            if (e.GetType() == EventType::GetStaticType()) {
                e.MarkHandled();
                return callback(static_cast<EventType &>(e));
            }
            return false;
        }

      private:
        Event &e;
    };

    template <typename EventType> class Signal {
      public:
        using Listener = std::function<void(EventType &)>;
        static_assert(std::is_base_of<Event, EventType>(),
                      "Event type is not inherited from event struct");

        size_t Subscribe(Listener listener) {
            listeners.push_back(listener);
            return idCount++;
        }

        void Unsubscribe(size_t id) {
            listeners.erase(id);
        }

        void UnsubscribeAll() {
            listeners.clear();
        }

        void Fire(EventType &event) {
            for (auto &l : listeners) {
                l(event);

                if (event.IsHandled())
                    break;
            }
        }

      private:
        size_t idCount = 0;
        std::vector<Listener> listeners;
    };
} // namespace gle