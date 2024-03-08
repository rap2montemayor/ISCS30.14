#include "Scene.hpp"

const std::string textureConfig = "Data/Textures.cfg";
const std::string spriteSheet = "SpriteSheet";
const std::string background = "Background";
const std::string tileTypes = "Data/Tiles.cfg";
const std::string levelData = "Data/Level.cfg";
const std::string spriteData = "Data/Sprites.cfg";

Scene::Scene(poly::Window& window) :
    poly::Scene(window), ecsManager(ecs), controller(ecs), physics(ecs),
    spriteManager(), tileFactory(ecs, spriteManager), level(ecs, tileFactory),
    renderer(ecs, window, controller) {
    poly::logInfo("Scene::Scene");
}

void Scene::init() {
    poly::logInfo("Starting Scene::init");
    
    textureManager.loadConfig(textureConfig);
    textureManager.request(spriteSheet);
    textureManager.request(background);
    spriteManager.setSpriteSheet(textureManager.getResource(spriteSheet));
    spriteManager.readSpriteData(spriteData);
    tileFactory.readTiles(tileTypes);
    createPlayer();
    level.loadLevel(levelData);

    poly::logInfo("Ending Scene::init");
}

void Scene::createPlayer() {
    poly::logInfo("Starting Scene::createPlayer");

    poly::EntityID player = ecs.createEntity();
    ecs.setData<Acceleration>(player, {0.f, 0.f});
    ecs.setData<Velocity>(player, {0.f, 0.f});
    ecs.setData<Position>(player, {0.f, 1116.f});
    // There's this weird scaling issue if I set this to {50, 100}
    ecs.setData<Size>(player, {49.f, 100.f});
    ecs.setData<Collision>(player, {0});
    ecs.setData<Sprites>(player, {});
    physics.player = player;

    Sprites& playerSprites = ecs.getData<Sprites>(player);
    playerSprites.endSprite = 6;
    playerSprites.spriteSheet = textureManager.getResource(spriteSheet);
    const std::pair<int, std::string> spriteRects[] = {
        {0, "IdleLeft"},
        {1, "IdleRight"},
        {2, "MoveLeft1"},
        {3, "MoveRight1"},
        {4, "MoveLeft2"},
        {5, "MoveRight2"},
    };
    for (auto [i, str] : spriteRects) {
        const int id = spriteManager.getSpriteID(str);
        playerSprites.spriteRects[i] = spriteManager.getSpriteRect(id);
    }

    controller.setPlayer(player);

    poly::logInfo("Ending Scene::createPlayer");
}

void Scene::processInput() {
    controller.updateInputStates();
}

void Scene::render() {
    sf::View view;
    auto& [posx, posy] = ecs.getData<Position>(controller.getPlayer());
    auto [sizex, sizey] = window.getDimensions();

    sf::RectangleShape rect({(float) sizex, (float) sizey});
    rect.setFillColor(sf::Color::White);
    rect.setTexture(textureManager.getResource(background));
    window.render(rect);

    view.setSize({(float) sizex, (float) sizey});
    view.setCenter(posx+50, posy+50);
    window.setView(view);
    renderer.render();
    window.setView(window.getDefaultView());

    // poly::logInfo("player is at", posx, posy);
    // auto& [posx2, posy2] = ecs.getData<Position>(10);
    // poly::logInfo("random block is at", posx2, posy2);
}

void Scene::update(double deltaTime) {
    // poly::logInfo("delta time:", deltaTime);
    controller.updatePlayer();
    physics.update(deltaTime);
    renderer.updatePlayerSprites(deltaTime);
}

void Scene::exit() {
    // no cleanup
}
