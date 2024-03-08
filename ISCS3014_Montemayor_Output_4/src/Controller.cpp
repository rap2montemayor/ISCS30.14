#include "Controller.hpp"

using Keyboard = sf::Keyboard;
using Key = sf::Keyboard::Key;

Controller::Controller() : inputState(None) {
    poly::logInfo("Controller::Controller");
}

void Controller::updateInputStates() {
    std::pair<Key, InputState> inputMappings[] {
        {Key::Up,    InputState::Up},
        {Key::Down,  InputState::Down},
        {Key::Left,  InputState::Left},
        {Key::Right, InputState::Right},
        {Key::Z,     InputState::Shoot},
        {Key::X,     InputState::Bomb}
    };

    for (auto& [key, input] : inputMappings) {
        if (Keyboard::isKeyPressed(key)) {
            inputState |= input;
        } else {
            inputState &= ~input;
        }
    }
}

bool Controller::isPressed(const InputState& input) {
    return inputState & input;
}
