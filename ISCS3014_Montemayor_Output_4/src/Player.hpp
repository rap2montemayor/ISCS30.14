#ifndef SRC_PLAYER_HPP_
#define SRC_PLAYER_HPP_

#include <cmath>

#include <Poly/EntityComponentSystem.hpp>
#include <Poly/Logging.hpp>

#include "Components.hpp"
#include "Constants.hpp"
#include "Controller.hpp"
#include "ParticleManager.hpp"
#include "SpriteManager.hpp"

class Player {
public:
    Player(poly::ECS& ecs, Controller& controller,
        ParticleManager& particleManager, SpriteManager& spriteManager);
    void init();
    void update(double deltaTime);
    void processInput();
    poly::EntityID getID();
    int& getFire();
    bool isDead();

private:
    poly::EntityID id;
    poly::ECS& ecs;
    Controller& controller;
    ParticleManager& particleManager;
    SpriteManager& spriteManager;

    double shotCooldown;
    int fire;
    bool dead;
};

#endif // SRC_PLAYER_HPP_
