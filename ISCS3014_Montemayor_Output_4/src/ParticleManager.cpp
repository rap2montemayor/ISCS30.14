#include "ParticleManager.hpp"


ParticleManager::ParticleManager(poly::ECS& ecs, SpriteManager& spriteManager)
    : ecs(ecs),spriteManager(spriteManager),
    rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}

void ParticleManager::update(double deltaTime) {
    ecs.runSystem<LifeTime>(
        [&](poly::EntityList& entities) {
            for (auto& id : entities) {
                double& remaining = ecs.getData<LifeTime>(id).remaining;
                auto& [sizex, sizey] = ecs.getData<Size>(id);
                remaining -= deltaTime;
                sizex -= 10*deltaTime;
                sizey -= 10*deltaTime;
                sizex = std::max(sizex, 0.f);
                sizey = std::max(sizey, 0.f);

                if (remaining <= 0) {
                    // poly::logInfo("deleting particle", id);
                    ecs.markForDeletion(id);
                }
            }
        }
    );
}

void ParticleManager::spawnParticle(const Position& spawnPos, const Size& size, const float vel) {
    poly::EntityID id = ecs.createEntity();
    ecs.setData<Position>(id, spawnPos);
    ecs.setData<Velocity>(id, {0, 0});
    ecs.setData<Size>(id, size);
    ecs.setData<LifeTime>(id, {2});
    ecs.setData<Sprite>(id, {
        spriteManager.getSpriteSheet(),
        spriteManager.getSpriteRect(spriteManager.getSpriteID("Particle"))
    });

    Position& pos = ecs.getData<Position>(id);
    Velocity& velocity = ecs.getData<Velocity>(id);
    pos.x += randint(-10, 10);
    pos.y += randint(-10, 10);

    velocity.x += randint(-vel, vel);
    velocity.y += randint(-vel, vel);
}

void ParticleManager::spawnExplosion(const Position& spawnPos) {
    auto& [x, y] = spawnPos;
    for (int i = 0; i < 25; ++i) {
        spawnParticle({x+randint(-10, 10), y+randint(-10, 10)}, {20, 20}, 500);
    }
    for (int i = 0; i < 5; ++i) {
        spawnParticle({x+randint(-10, 10), y+randint(-10, 10)}, {40, 40}, 500);
    }
}

int ParticleManager::randint(int l, int r) {
    return std::uniform_int_distribution<int>(l,r)(rng);
}