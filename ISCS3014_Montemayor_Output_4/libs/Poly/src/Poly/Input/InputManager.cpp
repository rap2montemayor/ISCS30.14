#include "Poly/Input/InputManager.hpp"

namespace poly {

void InputManager::processInput(InputContainer inputs) {
    for (sf::Event& e: inputs) {
        for (InputListener* i: listenerMap[e.type]) {
            i->callback(e);
        }
    }
}

void InputManager::addListener(InputListener& listener) {
    listenerMap[listener.getEventType()].push_back(&listener);
}

void InputManager::removeListener(InputListener& listener) {
    const sf::Event::EventType eventType = listener.getEventType();
    std::vector<InputListener*>& listeners = listenerMap[eventType];
    auto itr = std::find(listeners.begin(), listeners.end(), &listener);

    if (itr != listeners.end()) {
        listeners.erase(itr);
    }
    // else this listener was not registered
}

}
