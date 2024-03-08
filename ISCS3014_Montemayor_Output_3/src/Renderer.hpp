#pragma once

#include "Poly/Logging.hpp"
#include "Poly/EntityComponentSystem.hpp"
#include "Poly/Core.hpp"

#include "Components.hpp"
#include "Controller.hpp"

class Renderer {
public:
    Renderer(poly::ECS& ecs, poly::Window& window, Controller& controller);
    void render();
    void updatePlayerSprites(double deltaTime);
    void renderSystem(poly::EntityList entities);
private:
    poly::ECS& ecs;
    poly::Window& window;
    poly::EntityID player;
    Controller& controller;
};