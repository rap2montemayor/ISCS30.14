#include "Level.hpp"

Level::Level(poly::ECS& ecs, TileFactory& tileFactory)
    : ecs(ecs), tileFactory(tileFactory) {
    poly::logInfo("Level::Level");
}

void Level::loadLevel(const std::string& levelData) {
    poly::logInfo("Starting Level::loadLevel");

    // tilename, posx, posy
    std::ifstream ifs(levelData);
    if (ifs.is_open()) {
        std::string tileName;
        int rows, cols;
        ifs >> rows >> cols;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                ifs >> tileName;
                if (tileName == ".") continue;
                poly::EntityID id = ecs.createEntity();
                tileFactory.makeTile(tileName).registerEntity(ecs, id);
                ecs.getData<Position>(id) = {j*64.f, i*64.f};
                poly::logInfo("Created tile at", j*64.f, i*64.f);
            }
        }
    }

    poly::logInfo("Ending Level::loadLevel");
}