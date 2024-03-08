#include "Event.hpp"

namespace poly {

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
