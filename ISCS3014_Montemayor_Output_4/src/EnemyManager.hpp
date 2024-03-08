#ifndef SRC_ENEMYMANAGER_HPP_
#define SRC_ENEMYMANAGER_HPP_

#include <functional>
#include <fstream>

#include <Poly/EntityComponentSystem.hpp>
#include <Poly/Logging.hpp>

#include "Components.hpp"
#include "EnemyBehaviors.hpp"
#include "PairHash.hpp"
#include "ParticleManager.hpp"
#include "Physics.hpp"
#include "Player.hpp"
#include "ProjectileManager.hpp"
#include "SpriteManager.hpp"

// Handles creation, deletion of enemies
class EnemyManager {
public:
    EnemyManager(poly::ECS& ecs, ParticleManager& particleManager,
        Physics& physics, Player& player, ProjectileManager& projectileManager,
        SpriteManager& spriteManager);
    void update(double deltaTime);
    void spawnEnemy(const Position& pos, const Velocity& vel, std::function<void(EnemyBehavior&, double)> behavior);
    void handleCollisions();
    void loadEnemySpawns(const std::string& enemySpawnData);
    void deleteOffscreen();

private:
    poly::ECS& ecs;
    ParticleManager& particleManager;
    Physics& physics;
    Player& player;
    ProjectileManager& projectileManager;
    SpriteManager& spriteManager;

    double time;
    std::vector<std::pair<double, std::function<void()>>> spawns;
};

#endif // SRC_ENEMYMANAGER_HPP_
