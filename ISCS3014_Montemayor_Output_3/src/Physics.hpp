#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>
#include "Poly/Logging.hpp"
#include "Poly/EntityComponentSystem.hpp"

#include "Components.hpp"

class Physics {
public:
    Physics(poly::ECS& ecs);
    void update(double deltaTime);
    poly::EntityID player;

private:
    using EntityPair = std::pair<poly::EntityID, poly::EntityID>;
    std::vector<EntityPair> collisionPairs;

    poly::ECS& ecs;
    double deltaRemaining;

    void move(poly::EntityList entities, double deltaTime);
    void collisions(poly::EntityList entities, double deltaTime);
    bool intersecting(poly::EntityID id1, poly::EntityID id2);
    bool intersectsX(poly::EntityID& id1, poly::EntityID& id2, double deltaTime);
    bool intersectsY(poly::EntityID& id1, poly::EntityID& id2, double deltaTime);
    float getIntersectionTime(poly::EntityID& id1, poly::EntityID& id2, double deltaTime);
    void handleCollisions(double deltaTime);
    void setCollisionX(poly::EntityID id1, poly::EntityID id2);
    void setCollisionY(poly::EntityID id1, poly::EntityID id2);
    sf::FloatRect getRect(const Position& pos, const Size& size);
};