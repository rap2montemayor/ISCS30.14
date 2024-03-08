#pragma once

#include <algorithm>
#include <unordered_map>
#include <vector>

#include <SFML/Window.hpp>

#include "InputListener.hpp"
#include "../Core/Window.hpp"

namespace poly {

class InputManager {
    using ListenerMap = std::unordered_map<sf::Event::EventType, std::vector<InputListener*>>;
    ListenerMap listenerMap;

public:
    InputManager() = default;

    // Calls every input listener that listens for a particular event
    void processInput(InputContainer inputs);

    // Registers a listener under its respective event type
    void addListener(InputListener& listener);

    // Removes a listener from its respective event type
    void removeListener(InputListener& listener);
};

}
