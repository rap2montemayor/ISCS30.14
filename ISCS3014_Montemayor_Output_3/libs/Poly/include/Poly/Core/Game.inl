#include "Game.hpp"

namespace poly {

template <typename NewScene>
void Game::setStartScene() {
    static_assert(std::is_base_of<Scene, NewScene>());
    currentScene = std::make_unique<NewScene>(window);
    currentScene->init();
}

}
