#include "Event.hpp"

namespace poly {

template <>
class Event<void> {
    std::vector<EventListener<void>*> listeners;

public:
    Event() = default;

    void fireEvent() {
        for (EventListener<void>* listener: listeners) {
            listener->callback();
        }
    }

    void addListener(EventListener<void>& listener) {
        listeners.push_back(&listener);
    }

    void removeListener(EventListener<void>& listener) {
        auto itr = std::find(listeners.begin(), listeners.end(), &listener);
        if (itr != listeners.end()) {
            listeners.erase(itr);
        }
    }
};


template <class EventArgs>
void Event<EventArgs>::fireEvent(EventArgs e) {
    for (EventListener<EventArgs>* listener: listeners) {
        listener->callback(e);
    }
}

template <class EventArgs>
void Event<EventArgs>::addListener(EventListener<EventArgs>& listener) {
    listeners.push_back(&listener);
}

template <class EventArgs>
void Event<EventArgs>::removeListener(EventListener<EventArgs>& listener) {
    auto itr = std::find(listeners.begin(), listeners.end(), &listener);
    if (itr != listeners.end()) {
        listeners.erase(itr);
    }
}

}
