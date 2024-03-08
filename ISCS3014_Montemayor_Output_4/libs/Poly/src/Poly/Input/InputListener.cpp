#include "Poly/Input/InputListener.hpp"

namespace poly {

InputListener::InputListener(sf::Event::EventType eventType,
        std::function<void(sf::Event&)> callback)
    : eventType(eventType)
    , callback(callback) {}

sf::Event::EventType InputListener::getEventType() {
    return eventType;
}

}
