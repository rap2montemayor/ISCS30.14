#include "SpriteManager.hpp"

SpriteManager::SpriteManager() : nextSpriteID(0), spriteSheet(nullptr) {
    // Might not really need this. May avoid vector spookiness.
    spriteRects.reserve(32);
}

int SpriteManager::registerSpriteType(const std::string& spriteName) {
    spriteIDs[spriteName] = nextSpriteID;
    spriteRects.emplace_back();
    return nextSpriteID++;
}

int SpriteManager::getSpriteID(const std::string& SpriteName) {
    return spriteIDs[SpriteName];
}

void SpriteManager::setSpriteRect(int id, sf::IntRect textureRect) {
    spriteRects[id] = textureRect;
}

const sf::IntRect& SpriteManager::getSpriteRect(int id) {
    return spriteRects[id];
}

void SpriteManager::readSpriteData(const std::string& SpriteData) {
    Logger::logInfo("Starting SpriteManager::readSpriteData");

    std::ifstream ifs(SpriteData);
    if (ifs.is_open()) {
        int x, y, sizex, sizey;
        std::string name;
        while (ifs.good()) {
            ifs >> std::ws >> x >> y >> sizex >> sizey >> name >> std::ws;
            int id = registerSpriteType(name);
            setSpriteRect(id, {x, y, sizex, sizey});
            spriteIDs[name] = id;

            // Should be replaced with sstream
            std::string msg
                = std::to_string(x) + " "
                + std::to_string(y) + " "
                + std::to_string(sizex) + " "
                + std::to_string(sizey) + " "
                + name;
            Logger::logInfo("Created sprite: " + msg);
        }
    } else {
        Logger::logError("Sprite data not found");
    }

    Logger::logInfo("Ending SpriteManager::readSpriteData");
}

void SpriteManager::setSpriteSheet(sf::Texture* texture) {
    spriteSheet = texture;
}

const sf::Texture* SpriteManager::getSpriteSheet() {
    return spriteSheet;
}