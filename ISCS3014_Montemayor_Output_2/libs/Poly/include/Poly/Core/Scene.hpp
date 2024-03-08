#pragma once

#include "Window.hpp"

namespace poly {

class Game;

// Base class for scenes. Simply communicates with the game object for input,
// rendering, and updates.
// To use, subclass the scene and override all virtual constructors. Subclass
// must call the superclass constructor in its own constructor.
class Scene {
protected:
    Game& game;
    Scene(Game& game) : game(game) { }

public:
    virtual void processInput(InputContainer inputs) = 0;
    virtual void render(Window& window) = 0;
    virtual void update(double deltaTime) = 0;

    virtual void init() = 0;
    virtual void exit() = 0;
};

}
