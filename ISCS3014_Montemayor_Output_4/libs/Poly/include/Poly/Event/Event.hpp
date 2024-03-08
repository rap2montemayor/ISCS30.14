#pragma once

#include <algorithm>
#include <vector>

#include "EventListener.hpp"

namespace poly {

template <class EventArgs>
class Event {
    std::vector<EventListener<EventArgs>*> listeners;

public:
    Event() = default;

    // Calls the callback function of every listener
    void fireEvent(EventArgs e);

    // Registers a listener to this event's list of listeners
    void addListener(EventListener<EventArgs>& listener);

    // Removes a listener from this event's list of listeners
    void removeListener(EventListener<EventArgs>& listener);
};

// Specialization for void
template <>
class Event<void>;

}


#include "Event.inl"
