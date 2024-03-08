#include "Scene.hpp"

#include "Constants.hpp"
const std::string spriteSheet = "SpriteSheet";
const std::string textureConfig = "Data/Textures.cfg";
const std::string spriteData = "Data/SpriteData.cfg";
const std::string levelData = "Data/LevelData.cfg";
const std::string playerSpriteData = "Data/PlayerSprites.cfg";
const std::string tileData = "Data/TileData.cfg";
const std::string objectData = "Data/ObjectData.cfg";

Scene::Scene(poly::Game& game) :
    poly::Scene(game), tileManager(spriteManager),
    level(spriteManager, tileManager) {}

void Scene::init() {
    Logger::logInfo("Starting Scene::init");

    // Textures
    textureManager.loadConfig(textureConfig);
    textureManager.request(spriteSheet);

    // Sprite sheet
    sf::Texture* spriteSheetPtr = textureManager.getResource(spriteSheet);
    spriteManager.setSpriteSheet(spriteSheetPtr);
    spriteManager.readSpriteData(spriteData);

    // Tile data
    tileManager.readTileData(tileData);

    // Level data
    level.readLevelData(levelData);
    level.readObjectData(objectData);

    // Player sprites
    level.readPlayerSpriteData(playerSpriteData);

    level.init();

    Logger::logInfo("Ending Scene::init");   
}

void Scene::processInput(poly::InputContainer inputs) {
    // do nothing. Controller gets input from sf::Keyboard
}

void Scene::render(poly::Window& window) {
    level.render(window);
}

void Scene::update(double deltaTime) {
    // do nothing
    level.update(deltaTime);
}

void Scene::exit() {
    textureManager.release(spriteSheet);
}
