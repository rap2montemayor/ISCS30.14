#include "EventListener.hpp"

namespace poly {

template <class EventArgs>
EventListener<EventArgs>::EventListener(
        std::function<void(EventArgs)> callback) {
    this->callback = callback;
}

}
