#include "TileManager.hpp"

#include "Logger.hpp"

TileManager::TileManager(SpriteManager& spriteManager)
    : spriteManager(spriteManager), nextTileID(0) {}

void TileManager::readTileData(const std::string& tileData) {
    Logger::logInfo("Starting TileManager::readTileData");

    std::ifstream ifs(tileData);
    if (ifs.is_open()) {
        std::string tileName;
        int passable;
        int onEnter;
        int spriteCount;

        std::string spriteName;
        std::vector<int> sprites;
        while (ifs.good()) {
            ifs >> tileName >> passable >> onEnter >> spriteCount;
            sprites.clear();
            for (int i = 0; i < spriteCount; ++i) {
                ifs >> spriteName;
                int id = spriteManager.getSpriteID(spriteName);
                sprites.emplace_back(id);
                Logger::logInfo("Created tile type with sprite with id " + std::to_string(id));
            }
            
            tileIDs[tileName] = registerTileType<Tile>(sprites,
                bool(passable), EnterResponse(onEnter));
        }
    } else {
        Logger::logError("Unable to read tile data");
    }

    Logger::logInfo("Ending TileManager::readTileData");
}

int TileManager::getTileID(const std::string& tileName) {
    return tileIDs[tileName];
}

std::unique_ptr<Tile> TileManager::createTile(int tileID) {
    return tileFactory[tileID]();
}
