#include "Poly/Core/Game.hpp"

namespace poly {

Game::Game() : currentScene(nullptr), exiting(false) {
    setWindow(800, 600, "Game", sf::Style::Default & ~sf::Style::Resize);
}

void Game::start() {
    handleSceneSwitch();
    assert(currentScene != nullptr);
    while (not exiting) {
        handleSceneSwitch();
        processInput();
        update(clock.restart().asSeconds());
        render();
    }
    currentScene->exit();
}

void Game::processInput() {
    const InputContainer inputs = window.pollInput();
    // An input manager would be overkill here.
    const bool toClose = std::any_of(inputs.begin(), inputs.end(),
        [](const sf::Event& e) {
            return e.type == sf::Event::EventType::Closed; });
    if (toClose) {
        exit();
    } else {
        currentScene->processInput(inputs);
    }
}

void Game::render() {
    window.beginRender();
    currentScene->render(window);
    window.endRender();
}

void Game::update(double deltaTime) {
    currentScene->update(deltaTime);
    handleSceneSwitch();
}

void Game::handleSceneSwitch() {
    if (sceneSwitchHandler != nullptr) {
        sceneSwitchHandler();
        sceneSwitchHandler = nullptr;
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
