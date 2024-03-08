#ifndef SRC_PARTICLEMANAGER_HPP_
#define SRC_PARTICLEMANAGER_HPP_

#include <chrono>
#include <random>

#include <Poly/EntityComponentSystem.hpp>
#include <Poly/Logging.hpp>

#include "Components.hpp"
#include "SpriteManager.hpp"

class ParticleManager {
public:
    ParticleManager(poly::ECS& ecs, SpriteManager& spriteManager);

    void update(double deltaTime);
    void spawnParticle(const Position& spawnPos, const Size& size={10, 10}, const float vel=100);
    void spawnExplosion(const Position& pos);

private:
    int randint(int l, int r);

    poly::ECS& ecs;
    SpriteManager& spriteManager;

    std::mt19937 rng;
};

#endif // SRC_PARTICLEMANAGER_HPP_
