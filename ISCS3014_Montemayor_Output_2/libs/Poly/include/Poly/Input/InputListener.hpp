#pragma once

#include <functional>

#include <SFML/Window.hpp>

namespace poly {

class InputListener {
    sf::Event::EventType eventType;

public:
    std::function<void(sf::Event&)> callback;

    // Force input listeners to be constructed with a callback.
    InputListener() = delete;

    // Constructor takes a callback function. Make sure to bind member functions
    // first.
    InputListener(sf::Event::EventType eventType,
        std::function<void(sf::Event&)> callback);

    // Returns the event type that this listener responds to.
    sf::Event::EventType getEventType();
};

}
