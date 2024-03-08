#include "ECSManager.hpp"

ECSManager::ECSManager(poly::ECS& ecs) : ecs(ecs) {
    poly::logInfo("Starting ECSManager::ECSManager");

    ecs.registerComponent<Position>();
    poly::logInfo("Registered Position");

    ecs.registerComponent<Velocity>();
    poly::logInfo("Registered Velocity");

    ecs.registerComponent<Acceleration>();
    poly::logInfo("Registered Acceleration");

    ecs.registerComponent<Size>();
    poly::logInfo("Registered Size");

    ecs.registerComponent<Collision>();
    poly::logInfo("Registered Collision");

    ecs.registerComponent<Sprites>();
    poly::logInfo("Registered Sprites");

    poly::logInfo("Ending ECSManager::ECSManager");
}