#pragma once

#include "Poly/Core/Window.hpp"
#include "Poly/Utils.hpp"

#include "TileManager.hpp"
#include "SpriteManager.hpp"
#include "Player.hpp"

// Contains functions for rendering and animating the level

class Renderer {
public:
    Renderer(SpriteManager& spriteManager, Player& player);
    void update(double deltaTime);
    void animateTiles(TileGrid& grid);
    void renderTile(Tile& tile, poly::Window& window, int i, int j);
    void renderPlayer(poly::Window& window);
    void moveSprite(const Direction& direction);
    void moveAnimate(const Direction& direction);
    void changePlayerFace(const Direction& direction);
    
    // delays a function call from occurring until duration has passed
    void timedCallback(double duration, std::function<void()> callback,
        double curTime=0, double deltaTime=0);

private:
    sf::RectangleShape rect;
    poly::CallbackQueue<double> timedCallbacks;
    poly::Animator animator;
    SpriteManager& spriteManager;
    Player& player;


};