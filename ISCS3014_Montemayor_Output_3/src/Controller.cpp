#include "Controller.hpp"

#include <bitset>

using Keyboard = sf::Keyboard;
using Key = sf::Keyboard::Key;

Controller::Controller(poly::ECS& ecs) : ecs(ecs), 
    inputState(None), enabledInputs(All) {
    poly::logInfo("Controller::Controller");
}

void Controller::updateInputStates() {
    const bool left = Keyboard::isKeyPressed(Key::Left);
    const bool right = Keyboard::isKeyPressed(Key::Right);
    const bool jump = Keyboard::isKeyPressed(Key::Space);
    const bool reset = Keyboard::isKeyPressed(Key::R);
    const bool both = left and right;

    const bool leftEnabled = isEnabled(InputState::Left);
    const bool rightEnabled = isEnabled(InputState::Right);
    const bool jumpEnabled = isEnabled(InputState::Jump);
    const bool bothEnabled = leftEnabled and rightEnabled;

    // May want refactor this
    if (leftEnabled) {
        if (left) {
            inputState |= InputState::Left;
        } else {
            inputState &= ~InputState::Left;
        }
    }

    if (rightEnabled) {
        if (right) {
            inputState |= InputState::Right;
        } else {
            inputState &= ~InputState::Right;
        }
    }

    if (bothEnabled and both) {
        inputState &= ~InputState::Left;
        inputState &= ~InputState::Right;
    }
    
    if (jumpEnabled) {
        if (jump) {
            inputState |= InputState::Jump;
        } else {
            inputState &= ~InputState::Jump;
        }
    }

    if (reset) {
        inputState |= InputState::Reset;
    } else {
        inputState &= ~InputState::Reset;
    }
}

bool Controller::isPressed(const InputState& input) {
    return inputState & input;
}

void Controller::enableInput(const InputState& inputs) {
    enabledInputs |= inputs;
}

void Controller::disableInput(const InputState& inputs) {
    enabledInputs &= ~inputs;
}

bool Controller::isEnabled(const InputState& input) {
    return enabledInputs & input;
}

void Controller::setPlayer(poly::EntityID player) {
    this->player = player;
}

poly::EntityID Controller::getPlayer() {
    return player;
}

void Controller::updatePlayer() {
    const float eps = 1e-4;
    const float accel = 5000.f;
    const float gravity = 2500.f;

    const bool left = isPressed(InputState::Left);
    const bool right = isPressed(InputState::Right);
    const bool jump = isPressed(InputState::Jump);

    auto [accelx, accely] = ecs.getData<Acceleration>(player);
    auto [velx, vely] = ecs.getData<Velocity>(player);
    auto [collisions] = ecs.getData<Collision>(player);

    if (right) {
        if (velx < 0) {
            accelx = 2*accel;
        } else {
            accelx = accel;
        }
    } else if (left) {
        if (velx > 0) {
            accelx = -2*accel;
        } else {
            accelx = -accel;
        }
    } else {
        if (velx > eps) {
            accelx = -accel;
        } else if (velx < -eps) {
            accelx = accel;
        } else {
            velx = 0;
            accelx = 0;
        }
    }

    bool grounded = collisions & Collision::Below;
    if (jump and grounded) {
        vely = -1000;
    }

    ecs.setData<Velocity>(player, {velx, vely});
    ecs.setData<Acceleration>(player, {accelx, gravity});

    if (isPressed(InputState::Reset)) {
        ecs.setData<Position>(player, {0.f, 1116.f});
    }
}