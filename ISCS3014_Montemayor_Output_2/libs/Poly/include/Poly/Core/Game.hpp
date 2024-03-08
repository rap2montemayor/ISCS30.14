#pragma once

#include <cassert>
#include <functional>
#include <type_traits>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Window.hpp"
#include "Scene.hpp"

namespace poly {

// Base class for games. Handles coordination between the window and scenes,
// scene management, passing input events from window to scene, and scene
// updates.
// To use, create a game object, call switchScene() with the initial scene
// specified in the template argument, then call start();
class Game {
    std::unique_ptr<Scene> currentScene;
    std::function<void()> sceneSwitchHandler;
    sf::Clock clock;
    bool exiting;

protected:
    Window window;

public:
    Game();

    // Calls init(), starts the initial scene, and starts the game loop. Game
    // loop repeatedly calls handleSceneSwitch(), processInput(), update(), and
    // render in order. Loop stops when exit() is called, after which
    // currentScene->exit() is called;
    void start();

    // Switch to the scene specified in the template parameters. The actual
    // scene change is deferred until after update() is finished.
    template <class NewScene>
    void switchScene();

    // Sets exiting to false. This is meant to be called by scenes when if the
    // entire program has to be closed.
    void exit();

    // Reinitializes the window with the specified parameters.
    void setWindow(const unsigned int width, const unsigned int height,
		const char* title, const unsigned int style);

private:
    // Polls inputs from the window and passes them to the current scene. Also
    // check if a close event was triggered from the window.
    void processInput();

    // Passes the window to the current scene for rendering.
    void render();

    // Calls the current scene's update function and passes the amount of time
    // that has passed in seconds.
    void update(double deltaTime);

    // Scene switches are handled after all scene updates. This and the scene
    // switch handler are used to decouple those.
    void handleSceneSwitch();
};

}

#include "Game.inl"
