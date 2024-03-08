#include "Controller.hpp"

#include "Logger.hpp"

Controller::Controller() : direction(None), speedUp(false), enabled(true) {}

using Keyboard = sf::Keyboard;
using Key = sf::Keyboard::Key;

void Controller::updateInputState() {
    // The additional check after isKeyPressed has this really funny effect of
    // letting you alternate between two directions if you hold both of them at
    // the same time.
    
    // Directional input
    if (Keyboard::isKeyPressed(Key::Up) and direction != Up) {
        // Logger::logInfo("up pressed");
        direction = Up;
    } else if (Keyboard::isKeyPressed(Key::Down) and direction != Down) {
        // Logger::logInfo("down pressed");
        direction = Down;
    } else if (Keyboard::isKeyPressed(Key::Left) and direction != Left) {
        // Logger::logInfo("left pressed");
        direction = Left;
    } else if (Keyboard::isKeyPressed(Key::Right) and direction != Right) {
        // Logger::logInfo("right pressed");
        direction = Right;
    } else {
        direction = None;
    }
}

void Controller::updateSpeedupState() {
    if (Keyboard::isKeyPressed(Key::Space)) {
        speedUp = true;
    } else {
        speedUp = false;
    }
}

void Controller::enable() {
    enabled = true;
}

void Controller::disable() {
    enabled = false;
}

const Direction& Controller::getDirection() {
    return direction;
}

const bool& Controller::isSpeedUp() {
    return speedUp;
}

const bool& Controller::isEnabled() {
    return enabled;
}
