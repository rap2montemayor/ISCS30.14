#pragma once

#include "Player.hpp"
#include <SFML/Window.hpp>

class Controller {
public:
    Controller();
    // check if any of the buttons are being pressed
    // if they are, change direction
    void updateInputState();
    void updateSpeedupState();
    void enable();
    void disable();
    const Direction& getDirection();
    const bool& isSpeedUp();
    const bool& isEnabled();

private:
    // Controller state to be checked by the level
    Direction direction;
    bool speedUp;
    bool enabled;
};
