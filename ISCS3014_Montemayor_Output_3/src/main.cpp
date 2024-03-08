#include "Poly/Core/Game.hpp"
#include "Scene.hpp"

int main() {
    poly::Game game;
    game.setStartScene<Scene>();
    game.start();
    return 0;
}
