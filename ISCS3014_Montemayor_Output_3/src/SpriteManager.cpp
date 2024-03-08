#include "SpriteManager.hpp"

SpriteManager::SpriteManager() : nextSpriteID(0), spriteSheet(nullptr) {
    spriteRects.reserve(32);
    poly::logInfo("SpriteManager::SpriteManager");
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
    poly::logInfo("Starting SpriteManager::readSpriteData");

    std::ifstream ifs(SpriteData);
    if (ifs.is_open()) {
        int x, y, sizex, sizey;
        std::string name;
        while (ifs.good()) {
            ifs >> std::ws >> x >> y >> sizex >> sizey >> name >> std::ws;
            int id = registerSpriteType(name);
            setSpriteRect(id, {x, y, sizex, sizey});
            spriteIDs[name] = id;
        }
    } else {
        poly::logError("Could not load sprite data");
    }

    poly::logInfo("Ending SpriteManager::readSpriteData");
}

void SpriteManager::setSpriteSheet(sf::Texture* texture) {
    spriteSheet = texture;
}

sf::Texture* const SpriteManager::getSpriteSheet() {
    return spriteSheet;
}