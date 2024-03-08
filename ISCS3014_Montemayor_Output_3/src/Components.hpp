#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

struct Position {
    float x = 0;
    float y = 0;
};

struct Velocity {
    float x = 0;
    float y = 0;
};

struct Acceleration {
    float x = 0;
    float y = 0;
};

struct Size {
    float x = 0;
    float y = 0;
};

struct Collision {
    enum Direction {
        Above = 0b0001,
        Right = 0b0010,
        Below = 0b0100,
        Left  = 0b1000, 
    };

    unsigned int direction = 0;
};

struct Sprites {
    unsigned int currentSprite = 0;
    unsigned int endSprite = 0;
    double timeToNext = -1;
    sf::Texture* spriteSheet = nullptr;
    sf::IntRect spriteRects[8] = {};
};