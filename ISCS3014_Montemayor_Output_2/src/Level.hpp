#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "Poly/Core/Window.hpp"

#include "Controller.hpp"
#include "Player.hpp"
#include "Renderer.hpp"
#include "SpriteManager.hpp"
#include "TileManager.hpp"

// Moderately ugly object that coordinates a several parts of the code

class Level {
public:
    Level(SpriteManager& spriteManager, TileManager& tileManager);
    void render(poly::Window& window);
    void update(double deltaTime);
    void init();

    void readLevelData(const std::string& levelData);
    void readObjectData(const std::string& levelData);
    void readPlayerSpriteData(const std::string& playerData);
protected:
private:

    bool checkCollision(const Direction& direction);

    void movePlayer(Direction direction, bool animate);

    void onMoveEnd();

    bool handleTileEnter(EnterResponse response);

    TileGrid floorTiles;
    TileGrid objectTiles;
    Player player;
    Controller controller;    

    SpriteManager& spriteManager;
    TileManager& tileManager;

    Renderer renderer;
};