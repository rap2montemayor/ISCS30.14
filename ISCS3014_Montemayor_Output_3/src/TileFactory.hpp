#pragma once

#include <fstream>
#include <string>
#include <unordered_map>

#include "Poly/EntityComponentSystem.hpp"

#include "Components.hpp"
#include "SpriteManager.hpp"

struct Tile {
    Position pos;
    Velocity vel;
    Acceleration accel;
    Size size;
    Collision collision;
    Sprites sprites;

    void registerEntity(poly::ECS& ecs, poly::EntityID id);
};

class TileFactory {
public:
    TileFactory(poly::ECS& ecs, SpriteManager& spriteManager);

    // Read tile types
    void readTiles(const std::string& tileData);
    Tile makeTile(const std::string& tileType);

private:
    poly::ECS& ecs;
    SpriteManager& spriteManager;
    std::unordered_map<std::string, Tile> tileTypes;
};