#include "Poly/Core/Game.hpp"
#include "Scene.hpp"

int main() {
    poly::Game game;
    game.switchScene<Scene>();
    game.start();
    return 0;
}
