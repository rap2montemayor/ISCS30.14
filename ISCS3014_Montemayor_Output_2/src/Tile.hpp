#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum EnterResponse { NoResponse, Continue, MoveUp, MoveDown, MoveLeft, MoveRight };

class Tile {
public:
    Tile(const std::vector<int>& animationSprites, bool passable,
        EnterResponse onEnter);

    bool getPassable();
    const std::vector<int>& getSprites();
    void nextSprite();
    int getCurrentSpriteID();
    EnterResponse getOnEnter();

protected:
    std::vector<int> sprites;
    int spriteIndex;
    bool passable;
    EnterResponse onEnter;
};
