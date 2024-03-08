#pragma once

#include <SFML/Graphics.hpp>

#include "Poly/EntityComponentSystem.hpp"
#include "Poly/Core.hpp"
#include "Poly/ResourceManager.hpp"
#include "Poly/Logging.hpp"

#include "Controller.hpp"
#include "Components.hpp"
#include "ECSManager.hpp"
#include "Physics.hpp"
#include "Level.hpp"
#include "SpriteManager.hpp"
#include "TileFactory.hpp"
#include "Renderer.hpp"

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

    poly::TextureManager textureManager;
    poly::ECS ecs;

    ECSManager ecsManager;
    Controller controller;
    Physics physics;
    SpriteManager spriteManager;
    TileFactory tileFactory;
    Level level;
    Renderer renderer;
};

