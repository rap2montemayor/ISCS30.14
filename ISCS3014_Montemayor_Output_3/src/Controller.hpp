#pragma once

#include <SFML/Window.hpp>

#include "Poly/EntityComponentSystem.hpp"
#include "Poly/Logging.hpp"

#include "Components.hpp"

enum InputState {
    None  = 0b0000,
    Left  = 0b0001,
    Right = 0b0010,
    Jump  = 0b0100,
    Reset = 0b1000,
    All   = 0b1111,
};

// Doesn't poll for events. Checks sfml's keyboard states directly.

class Controller {
public:
    Controller(poly::ECS& ecs);

    void updateInputStates();
    bool isPressed(const InputState& input);
    void enableInput(const InputState& input);
    void disableInput(const InputState& input);
    bool isEnabled(const InputState& input);
    poly::EntityID getPlayer();
    void setPlayer(poly::EntityID player);
    void updatePlayer();

private:
    poly::ECS& ecs;
    poly::EntityID player;
    unsigned int inputState;
    unsigned int enabledInputs;
};