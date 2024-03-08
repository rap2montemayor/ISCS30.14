#include "Player.hpp"

#include "Constants.hpp"
#include "Logger.hpp"

Player::Player() : Player(0, 0) {}

Player::Player(int startRow, int startCol) :
    gridPosition(startRow, startCol),
    spritePosition(startCol*tileSize.first, startRow*tileSize.second),
    spriteIndex(IdleDown), moveDirection(Down), faceDirection(Down) {}

void Player::changeSprite(PlayerSprite index) {
    spriteIndex = index;
}

void Player::move(Direction direction) {
    auto& [row, col] = gridPosition;
    switch (direction) {
    case Direction::Up:
        --row;
        break;
    case Direction::Down:
        ++row;
        break;
    case Direction::Left:
        --col;
        break;
    case Direction::Right:
        ++col;
        break;
    default:
        break;
    }

    Logger::logInfo("player moved to "
        + std::to_string(row) + " " + std::to_string(col));
}

void Player::setSpritePosition(double x, double y) {
    spritePosition = {x, y};
}

void Player::setSprites(const std::vector<int>& sprites) {
    this->sprites = sprites;
}

void Player::setMoveDirection(Direction direction) {
    moveDirection = direction;
}

void Player::setFaceDirection(Direction direction) {
    faceDirection = direction;
}

const std::pair<double, double>& Player::getSpritePosition() {
    return spritePosition;
}

const std::pair<int, int>& Player::getGridPosition() {
    return gridPosition;
}

const std::vector<int>& Player::getSprites() {
    return sprites;
}

const PlayerSprite Player::getSpriteIndex() {
    return spriteIndex;
}

const int Player::getCurrentSpriteID() {
    return sprites[spriteIndex];
}

const Direction& Player::getMoveDirection() {
    return moveDirection;
}

const Direction& Player::getFaceDirection() {
    return faceDirection;
}

const std::pair<int, int> Player::getEndPosition(const Direction& direction) {
    auto [row, col] = getGridPosition();
    switch (direction) {
    case Up:
        --row;
        break;
    case Down:
        ++row;
        break;
    case Left:
        --col;
        break;
    case Right:
        ++col;
        break;
    default:
        break;
    }
    return {row, col};
}
