#pragma once

#include "Poly/Logging.hpp"
#include "Poly/EntityComponentSystem.hpp"
#include "Components.hpp"

// probably didn't need this.

class ECSManager {
public:
    ECSManager(poly::ECS& ecs);
private:
    poly::ECS& ecs;
};