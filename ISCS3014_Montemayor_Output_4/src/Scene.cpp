#include "Scene.hpp"

const std::string background     = "Background";
const std::string enemySpawnData = "Data/EnemySpawns.cfg";
const std::string spriteData     = "Data/Sprites.cfg";
const std::string spriteSheet    = "SpriteSheet";
const std::string textureConfig  = "Data/Textures.cfg";

Scene::Scene(poly::Window& window)
    : poly::Scene(window),
    enemyManager(ecs, particleManager, physics, player,
        projectileManager, spriteManager),
    particleManager(ecs, spriteManager),
    physics(ecs),
    player(ecs, controller, particleManager, spriteManager),
    projectileManager(ecs, particleManager, physics, player, spriteManager),
    renderer(ecs, window) {}

void Scene::init() {
    poly::logInfo("Starting Scene::init");

    textureManager.loadConfig(textureConfig);
    textureManager.request(spriteSheet);
    textureManager.request(background);

    spriteManager.setSpriteSheet(textureManager.getResource(spriteSheet));
    spriteManager.readSpriteData(spriteData);

    initializeECS();
    player.init();
    enemyManager.loadEnemySpawns(enemySpawnData);

    poly::logInfo("Ending Scene::init");
}

void Scene::initializeECS() {
    ecs.registerComponent<Acceleration>();
    ecs.registerComponent<EnemyBehavior>();
    ecs.registerComponent<EntityType>();
    ecs.registerComponent<Health>();
    ecs.registerComponent<LifeTime>();
    ecs.registerComponent<Position>();
    ecs.registerComponent<ProjectileBehavior>();
    ecs.registerComponent<ProjectileType>();
    ecs.registerComponent<Radius>();
    ecs.registerComponent<Size>();
    ecs.registerComponent<Sprite>();
    ecs.registerComponent<Velocity>();
}

void Scene::processInput() {
    controller.updateInputStates();
    player.processInput();
}

void Scene::render() {
    sf::RectangleShape rect;
    rect.setPosition({0, 0});
    rect.setSize({1280, 720});
    rect.setFillColor(sf::Color::Black);
    window.render(rect);

    rect.setPosition({playfieldLeft, playfieldTop});
    rect.setSize({playfieldRight-playfieldLeft, playfieldBottom-playfieldTop});
    rect.setFillColor(sf::Color::White);
    rect.setTexture(textureManager.getResource(background));
    window.render(rect);

    renderer.render();
}

void Scene::update(double deltaTime) {
    physics.update(deltaTime);
    player.update(deltaTime);

    enemyManager.update(deltaTime);
    projectileManager.update(deltaTime);
    
    projectileManager.handleCollisions();
    enemyManager.handleCollisions();

    projectileManager.deleteOffscreen();
    enemyManager.deleteOffscreen();

    particleManager.update(deltaTime);  

    ecs.deleteMarkedEntities();
}

void Scene::exit() {
    // no cleanup
}
