#include "EnemyManager.hpp"

EnemyManager::EnemyManager(poly::ECS& ecs, ParticleManager& particleManager,
    Physics& physics, Player& player, ProjectileManager& projectileManager,
    SpriteManager& spriteManager)
    : ecs(ecs), particleManager(particleManager), physics(physics),
    player(player), projectileManager(projectileManager),
    spriteManager(spriteManager), time(0) {}

void EnemyManager::update(double deltaTime) {
    time += deltaTime;

    while (not spawns.empty()) {
        if (spawns.back().first <= time) {
            spawns.back().second();
            spawns.pop_back();
        } else {
            break;
        }
    }

    ecs.runSystem<EnemyBehavior>(
        [&](poly::EntityList& entities) {
            for (auto& id : entities) {
                auto& behavior = ecs.getData<EnemyBehavior>(id);
                auto& [health] = ecs.getData<Health>(id);
                behavior.update(deltaTime);

                if (health <= 0) {
                    particleManager.spawnExplosion(ecs.getData<Position>(id));
                    if (player.getID() != id) {
                        ecs.markForDeletion(id);
                    }
                }

                while (behavior.fire > 0) {
                    if (not player.isDead()) {
                        projectileManager.enemyShoot(id);
                    }
                    --behavior.fire;
                }
            }
        }
    );
}

void EnemyManager::spawnEnemy(const Position& pos, const Velocity& vel,
        std::function<void(EnemyBehavior&, double)> behavior=EnemyBehavior::noUpdate) {
    poly::EntityID id = ecs.createEntity();
    ecs.setData<EnemyBehavior>(id, {});
    ecs.setData<EntityType>(id, {EntityType::Enemy});
    ecs.setData<Health>(id, {5});
    ecs.setData<Position>(id, pos);
    ecs.setData<Radius>(id, {25});
    ecs.setData<Size>(id, {50, 50});
    ecs.setData<Velocity>(id, vel);
    ecs.setData<Sprite>(id, {
        spriteManager.getSpriteSheet(),
        spriteManager.getSpriteRect(spriteManager.getSpriteID("Cirno"))
    });

    auto& enemyBehavior = ecs.getData<EnemyBehavior>(id);
    enemyBehavior.behaviorCallback = behavior;

    // poly::logInfo("Enemy spawned", id);
}

// enemy-player collisions
void EnemyManager::handleCollisions() {
    std::unordered_set<CollisionPair>& collisions = physics.getCollisions();

    auto isEntity = [&](const poly::EntityID& id) {
        return ecs.hasData<EntityType>(id);
    };

    const poly::EntityID& playerID = player.getID();
    std::unordered_set<CollisionPair> evaluated;

    for (const auto& [id1, id2] : collisions) {
        if (not (isEntity(id1) and isEntity(id2))) {
            continue;
        }
        evaluated.emplace(id1, id2);
        if (id1 == playerID or id2 == playerID) {
            ecs.setData<Health>(id1, {0});
            ecs.setData<Health>(id2, {0});
        }
    }

    for (const CollisionPair& collision : evaluated) {
        collisions.erase(collision);
    }
}

void EnemyManager::loadEnemySpawns(const std::string& enemySpawnData) {
    poly::logInfo("Starting EnemyManager::loadEnemySpawns");
    // // time behavior posx posy velx vely

    auto shoot = EnemyBehavior::shootUpdate;
    auto noShoot = EnemyBehavior::noUpdate;

    std::ifstream ifs(enemySpawnData);
    if (ifs.is_open()) {
        double spawnTime;
        std::string behavior;
        float posx, posy;
        float velx, vely;
        while (ifs.good()) {
            ifs >> std::ws >> spawnTime >> behavior >> posx >> posy >> velx >> vely;
            auto behaviorfunc = behavior == "shoot" ? shoot : noShoot;
            std::function<void()> spawnFunc = [posx, posy, velx, vely, behaviorfunc, this]() {
                spawnEnemy({posx, posy}, {velx, vely}, behaviorfunc);
            };
            spawns.emplace_back(spawnTime, spawnFunc);
        }
    }

    using SpawnerPair = std::pair<double, std::function<void()>>;
    std::sort(spawns.rbegin(), spawns.rend(),
        [&](SpawnerPair& lhs, SpawnerPair& rhs) {
            return lhs.first < rhs.first;
        }
    );
    poly::logInfo("Ending EnemyManager::loadEnemySpawns");
}

void EnemyManager::deleteOffscreen() {
    ecs.runSystem<EntityType>([&](poly::EntityList& entities) {
        for (auto& id : entities) {
            Position& pos = ecs.getData<Position>(id);
            EntityType& type = ecs.getData<EntityType>(id);
            if (type.type == EntityType::Player) {
                continue;
            }
            if (pos.x < playfieldLeft or pos.y > playfieldBottom
                or pos.y < playfieldTop) {
                ecs.markForDeletion(id);
                // poly::logInfo("deleting enemy", id);
            }
        }
    });
}