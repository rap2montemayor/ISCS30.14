#include "Poly/Core/Game.hpp"

namespace poly {

Game::Game() : currentScene(nullptr), exiting(false) {
    setWindow(1280, 720, "Game", sf::Style::Default & ~sf::Style::Resize);
}

void Game::start() {
    assert(currentScene != nullptr);
    while (not exiting) {
        handleSceneSwitch();
        processInput();
        update(clock.restart().asSeconds());
        render();
    }
}

void Game::processInput() {
    window.pollInput();
    const InputContainer& inputs = window.getInputs();
    const bool toClose = std::any_of(inputs.begin(), inputs.end(),
        [](const sf::Event& e) {
            return e.type == sf::Event::EventType::Closed;
        }
    );
    if (toClose) {
        exit();
    } else {
        currentScene->processInput();
    }
}

void Game::render() {
    window.beginRender();
    currentScene->render();
    window.endRender();
}

void Game::update(double deltaTime) {
    currentScene->update(deltaTime);
    handleSceneSwitch();
}

void Game::handleSceneSwitch() {
    using SceneConstructor = Scene::SceneConstructor;
    if (currentScene->isExited()) {
        SceneConstructor constructor = currentScene->getNextSceneConstructor();
        if (constructor == nullptr) {
            exiting = true;
        } else {
            currentScene = constructor();
        }
    }
}

void Game::exit() {
    exiting = true;
}

void Game::setWindow(const unsigned int width, const unsigned int height,
        const char* title, const unsigned int style) {
    window.init(width, height, title, style);
}

}
