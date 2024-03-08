#ifndef SRC_SCENE_HPP_
#define SRC_SCENE_HPP_

#include <functional>

#include <SFML/Graphics.hpp>

#include <Poly/Core.hpp>
#include <Poly/EntityComponentSystem.hpp>
#include <Poly/Logging.hpp>
#include <Poly/ResourceManager.hpp>

#include "Components.hpp"
#include "Constants.hpp"
#include "Controller.hpp"
#include "EnemyManager.hpp"
#include "ParticleManager.hpp"
#include "Physics.hpp"
#include "Player.hpp"
#include "ProjectileBehaviors.hpp"
#include "ProjectileManager.hpp"
#include "Renderer.hpp"
#include "SpriteManager.hpp"

class Scene : public poly::Scene {
public:
    Scene(poly::Window& window);
    void init() override;
    void processInput() override;
    void render() override;
    void update(double deltaTime) override;
    void exit() override;

private:
    void createPlayer();
    void initializeECS();
    poly::ECS ecs;
    poly::TextureManager textureManager;

    Controller controller;
    EnemyManager enemyManager;
    ParticleManager particleManager;
    Physics physics;
    Player player;
    ProjectileManager projectileManager;
    Renderer renderer;
    SpriteManager spriteManager;
};

#endif // SRC_SCENE_HPP_
