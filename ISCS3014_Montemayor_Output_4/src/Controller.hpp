#ifndef SRC_CONTROLLER_HPP_
#define SRC_CONTROLLER_HPP_

#include <functional>
#include <unordered_map>

#include <SFML/Window.hpp>

#include <Poly/EntityComponentSystem.hpp>
#include <Poly/Logging.hpp>

#include "Components.hpp"

enum InputState {
    None  = 0,
    Up    = 1<<0, Down  = 1<<1,
    Left  = 1<<2, Right = 1<<3,
    Shoot = 1<<4, Bomb  = 1<<5,
    All = Up | Down | Left | Right | Shoot | Bomb
};

// Doesn't poll for events. Checks sfml's keyboard states directly.

class Controller {
public:
    Controller();
    void updateInputStates();
    bool isPressed(const InputState& input);

private:
    unsigned int inputState;
};


#endif // SRC_CONTROLLER_HPP_
