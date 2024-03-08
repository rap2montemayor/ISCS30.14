#include "EventListener.hpp"

namespace poly {

template <>
class EventListener<void> {
public:
    // Force event listeners to be constructed with a callback.
    EventListener() = delete;

    // Constructor takes a callback function. Note that member functions need to
    // be bound first.
    EventListener(std::function<void()> callback) {
        this->callback = callback;
    }

    std::function<void()> callback;
};

template <class EventArgs>
EventListener<EventArgs>::EventListener(
        std::function<void(EventArgs)> callback) {
    this->callback = callback;
}

}
