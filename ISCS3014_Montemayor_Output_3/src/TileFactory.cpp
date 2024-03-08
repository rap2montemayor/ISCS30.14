#include "TileFactory.hpp"

void Tile::registerEntity(poly::ECS& ecs, poly::EntityID id) {
    ecs.setData(id, pos);
    ecs.setData(id, vel);
    ecs.setData(id, accel);
    ecs.setData(id, size);
    ecs.setData(id, collision);
    ecs.setData(id, sprites);
}

TileFactory::TileFactory(poly::ECS& ecs, SpriteManager& spriteManager)
    : ecs(ecs), spriteManager(spriteManager) {
    poly::logInfo("TileFactory::TileFactory");
}

void TileFactory::readTiles(const std::string& tileData) {
    poly::logInfo("Starting TileFactory::readTiles");

    // tilename, spritecount
    // sprite1, sprite2, ...
    std::ifstream ifs(tileData);
    if (ifs.is_open()) {
        std::string name, spritename;
        int spritecount;
        while (ifs.good()) {
            ifs >> name >> spritecount;
            
            Tile& tile = tileTypes[name];
            tile.size = {64.f, 64.f};
            tile.sprites.endSprite = spritecount;
            for (int i = 0; i < spritecount; ++i) {
                ifs >> spritename;
                int id = spriteManager.getSpriteID(spritename);
                tileTypes[name].sprites.spriteRects[i]
                    = spriteManager.getSpriteRect(id);
                tileTypes[name].sprites.spriteSheet
                    = spriteManager.getSpriteSheet();
            }
        }
    } else {
        poly::logError("Could not load tile data");
    }

    poly::logInfo("Ending TileFactory::readTiles");
}

Tile TileFactory::makeTile(const std::string& tileType) {
    return tileTypes[tileType];
}
