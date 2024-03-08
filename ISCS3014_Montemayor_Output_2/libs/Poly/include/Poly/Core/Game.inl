#include "Game.hpp"

namespace poly {

template <typename NewScene>
void Game::switchScene() {
    static_assert(std::is_base_of<Scene, NewScene>());
    sceneSwitchHandler = [this] () {
        if (currentScene != nullptr) {
            currentScene->exit();
        }
        currentScene = std::make_unique<NewScene>(*this);
        currentScene->init();
    };
}

}
