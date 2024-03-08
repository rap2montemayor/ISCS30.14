#include "Tile.hpp"

Tile::Tile(const std::vector<int>& sprites, bool passable,
        EnterResponse onEnter) :
            sprites(sprites), spriteIndex(0), passable(passable),
            onEnter(onEnter) {}

bool Tile::getPassable() {
    return passable;
}

const std::vector<int>& Tile::getSprites() {
    return sprites;
}

void Tile::nextSprite() {
    spriteIndex = (spriteIndex+1) % sprites.size();
}

int Tile::getCurrentSpriteID() {
    return sprites[spriteIndex];
}

EnterResponse Tile::getOnEnter() {
    return onEnter;
}