#ifndef SRC_PHYSICS_HPP_
#define SRC_PHYSICS_HPP_

#include <algorithm>
#include <cmath>
#include <unordered_set>

#include <SFML/Graphics.hpp>

#include <Poly/Logging.hpp>
#include <Poly/EntityComponentSystem.hpp>

#include "Components.hpp"
#include "PairHash.hpp"

using CollisionPair = std::pair<poly::EntityID, poly::EntityID>;

class Physics {
public:
    Physics(poly::ECS &ecs);
    void update(double deltaTime);
    std::unordered_set<CollisionPair>& getCollisions();

private:
    poly::ECS& ecs;
    double deltaRemaining;

    std::unordered_set<CollisionPair> collisions;

    void accelerate(poly::EntityList& entities, double deltaTime);
    void move(poly::EntityList& entities, double deltaTime);
    void checkCollisions(poly::EntityList& entities);
};

#endif // SRC_PHYSICS_HPP_
