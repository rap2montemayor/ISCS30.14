#ifndef SRC_COMPONENTS_HPP_
#define SRC_COMPONENTS_HPP_

#include <SFML/Graphics.hpp>

struct Acceleration : public sf::Vector2f {
    Acceleration(const float& x=0, const float& y=0)
        : sf::Vector2f(x, y) {}
};

struct EntityType {
    enum { Player, Enemy } type = Player;
};

struct Position : public sf::Vector2f {
    Position(const float& x=0, const float& y=0)
        : sf::Vector2f(x, y) {}
};

struct ProjectileType {
    enum { Player, Enemy } type = Player;
};

// Actually just used for collision detection
struct Radius {
    float r = 0;
};

struct Size : public sf::Vector2f {
    Size(const float& x=0, const float& y=0)
        : sf::Vector2f(x, y) {}
};

struct Velocity : public sf::Vector2f {
    Velocity(const float& x=0, const float& y=0)
        : sf::Vector2f(x, y) {}
};

struct Health {
    int health = 5;
};

struct LifeTime {
    double remaining = 1;
};

struct Sprite {
    sf::Texture* texture = nullptr;
    sf::IntRect textureRect;
};

#endif // SRC_COMPONENTS_HPP_
