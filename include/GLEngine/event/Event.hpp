#pragma once

#include <vector>
#include <functional>
#include <string>

namespace GLEngine {
    class Event {
        public:
        virtual ~Event() = default;

        bool IsHandled() { return isHandled; }
        void MarkHandled() { isHandled = true; }
        virtual std::string ToString() { return "BaseEvent"; }

        private:
        bool isHandled = false;
    };

    template<typename EventType>
    class Signal {
        public:
        using Listener = std::function<void(EventType&)>;
        static_assert(std::is_base_of(Event, EventType), "This is a invalid event type (it must inherit the event class)");

        void Subscribe(Listener listener) {
            listeners.push_back(listener);
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
        std::vector<Listener> listeners;
    };

    class EventDispatcher {
        public:
        EventDispatcher(Event &e) : event(e) {}

        template<typename Type, typename Function>
        bool Dispatch(const Function &func) {
            Type* casted = dynamic_cast<Type*>(&event);
            if (casted) {
                return func(*casted);
            }
            return false;
        }

        private:
        Event &event;
    };
}