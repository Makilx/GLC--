#pragma once

#include <GLEngine/pch.hpp>
#include <functional>

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

    template <typename EventT>
    class Signal {
      public:
        using Listener = std::function<void(EventT &)>;
        static_assert(std::is_base_of<Event, EventT>::value,
                      "Event type must inherit from Event");

        size_t Subscribe(Listener listener) {
            const size_t id = ++idCount;
            listeners.emplace_back(id, std::move(listener));
            return id;
        }

        template <typename T>
        size_t Subscribe(T *instance, void (T::*method)(EventT &)) {
            const size_t id = ++idCount;
            listeners.emplace_back(
                id, [=](EventT &event) { (instance->*method)(event); });
            return id;
        }

        void Unsubscribe(size_t id) {
            listeners.erase(
                std::remove_if(listeners.begin(), listeners.end(),
                               [&](auto &p) { return p.first == id; }),
                listeners.end());
        }

        void UnsubscribeAll() {
            listeners.clear();
        }

        void Fire(EventT &event) {
            for (auto &[id, listener] : listeners) {
                listener(event);
                if (event.IsHandled())
                    break;
            }
        }

      private:
        size_t idCount = 0;
        std::vector<std::pair<size_t, Listener>> listeners;
    };
} // namespace gle
