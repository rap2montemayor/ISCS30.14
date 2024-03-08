#pragma once

#include <string>

#include "Poly/EntityComponentSystem.hpp"
#include "Poly/Logging.hpp"

#include "Components.hpp"
#include "TileFactory.hpp"

#include <SFML/Graphics.hpp>

class Level {
public:
    Level(poly::ECS& ecs, TileFactory& tileFactory);
    void loadLevel(const std::string& levelData);
private:
    poly::ECS& ecs;
    TileFactory& tileFactory;
};

