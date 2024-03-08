#pragma once

#include <functional>

namespace poly {

template <class EventArgs>
class EventListener {
public:
    // Force event listeners to be constructed with a callback.
    EventListener() = delete;

    // Constructor takes a callback function. Note that member functions need to
    // be bound first.
    EventListener(std::function<void(EventArgs)> callback);

    std::function<void(EventArgs)> callback;
};

template <>
class EventListener<void>;

}

#include "EventListener.inl"
