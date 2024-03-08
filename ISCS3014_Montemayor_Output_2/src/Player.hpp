#pragma once

#include <vector>

enum Direction {
    None, Up, Down, Left, Right
};

enum PlayerSprite {
    IdleUp, IdleDown, IdleLeft, IdleRight,
    MoveUp1, MoveDown1, MoveLeft1, MoveRight1,
    MoveUp2, MoveDown2, MoveLeft2, MoveRight2
};

template <typename T>
using Coordinates = std::pair<T, T>;

// contains all the information and the interfaces for manipulating the player
// i.e. sprites, moving, changing direction, etc.

class Player {
public:
    Player();
    Player(int startx, int starty);

    void changeSprite(PlayerSprite index);

    // Move model in the direction specified
    // Sprite changes are not handled here.
    void move(Direction direction);
    void setSpritePosition(double x, double y);
    void setSprites(const std::vector<int>& sprites);

    void setMoveDirection(Direction direction);
    void setFaceDirection(Direction direction);

    const Coordinates<double>& getSpritePosition();
    const Coordinates<int>& getGridPosition();
    const std::vector<int>& getSprites();
    const PlayerSprite getSpriteIndex();
    const int getCurrentSpriteID();

    const Direction& getMoveDirection();
    const Direction& getFaceDirection();

    const std::pair<int, int> getEndPosition(const Direction& direction);

private:
    // use this for collision checks
    Coordinates<int> gridPosition;
    // use this for rendering
    Coordinates<double> spritePosition; 
    std::vector<int> sprites;
    PlayerSprite spriteIndex;
    Direction moveDirection;
    Direction faceDirection;
};