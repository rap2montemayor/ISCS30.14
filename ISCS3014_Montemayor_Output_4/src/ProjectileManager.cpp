#include "ProjectileManager.hpp"

ProjectileManager::ProjectileManager(poly::ECS& ecs,
    ParticleManager& particleManager, Physics& physics, Player& player,
    SpriteManager& spriteManager)
    : ecs(ecs), particleManager(particleManager), physics(physics),
    player(player), spriteManager(spriteManager) {}

void ProjectileManager::update(double deltaTime) {
    // get all projectile behaviors
    ecs.runSystem<ProjectileBehavior>(
        [&](poly::EntityList& entities) {
            for (auto& id : entities) {
                auto& behavior = ecs.getData<ProjectileBehavior>(id);
                behavior.targetPos = ecs.getData<Position>(player.getID());
                behavior.update(deltaTime);
            }
        }
    );

    // player was already updated by the scene
    int& playerFire = player.getFire();
    while (playerFire) {
        --playerFire;
        playerShoot();
    }
}

poly::EntityID ProjectileManager::createShot(const Position& pos, const Velocity& vel, const sf::IntRect& spriteRect) {
    poly::EntityID projectile = ecs.createEntity();
    ecs.setData<Position>(projectile, pos);
    ecs.setData<Size>(projectile, {25, 25});
    ecs.setData<Radius>(projectile, {10});
    ecs.setData<Velocity>(projectile, vel);
    ecs.setData<Sprite>(projectile, {
        spriteManager.getSpriteSheet(),
        spriteRect
    });
    return projectile;
}

void ProjectileManager::playerShoot() {
    poly::EntityID playerID = player.getID();
    Position& pos = ecs.getData<Position>(playerID);
    poly::EntityID projectile = createShot(
        pos, {2000, 0},
        spriteManager.getSpriteRect(spriteManager.getSpriteID("PlayerShot"))
    );
    ecs.setData<ProjectileType>(projectile, {ProjectileType::Player});

    // give the shot a behavior

    // poly::logInfo("Creating projectile", projectile);
}

void ProjectileManager::enemyShoot(poly::EntityID enemyID) {
    Position& enemyPos = ecs.getData<Position>(enemyID);
    poly::EntityID projectile = createShot(
        enemyPos,
        {-500, 0},
        spriteManager.getSpriteRect(spriteManager.getSpriteID("EnemyShot"))
    );
    ecs.setData<ProjectileType>(projectile, {ProjectileType::Enemy});
    ecs.setData<ProjectileBehavior>(projectile, {});

    auto& behavior = ecs.getData<ProjectileBehavior>(projectile);
    auto& pos = ecs.getData<Position>(projectile);
    auto& vel = ecs.getData<Velocity>(projectile);

    behavior.spawnBehavior = ProjectileBehavior::aimedSpawn;
    behavior.pos = &pos;
    behavior.vel = &vel;
    behavior.targetPos = ecs.getData<Position>(player.getID());
    behavior.start();
}

void ProjectileManager::deleteOffscreen() {
    ecs.runSystem<ProjectileType>([&](poly::EntityList& entities) {
        for (poly::EntityID& id : entities) {
            Position& pos = ecs.getData<Position>(id);
            if (pos.x > playfieldRight or pos.x < playfieldLeft
                    or pos.y > playfieldBottom or pos.y < playfieldTop) {
                ecs.markForDeletion(id);
            }
        }
    });
}

// enemy - projectile
// player - projectile
// projectile - projectile
void ProjectileManager::handleCollisions() {
    std::unordered_set<CollisionPair>& collisions = physics.getCollisions();

    auto isEntity = [&](const poly::EntityID& id) {
        return ecs.hasData<EntityType>(id);
    };

    auto isProjectile = [&](const poly::EntityID& id) {
        return ecs.hasData<ProjectileType>(id);
    };

    auto isPlayerProjectile = [&](const poly::EntityID& id) {
        return ecs.getData<ProjectileType>(id).type == ProjectileType::Player;
    };

    auto isEnemyProjectile = [&](const poly::EntityID& id) {
        return ecs.getData<ProjectileType>(id).type == ProjectileType::Enemy;
    };

    auto isPlayer = [&](const poly::EntityID& id) {
        return ecs.getData<EntityType>(id).type == EntityType::Player;
    };

    auto isEnemy = [&](const poly::EntityID& id) {
        return ecs.getData<EntityType>(id).type == EntityType::Enemy;
    };
    
    std::unordered_set<CollisionPair> evaluated;
    for (const auto& [id1, id2] : collisions) {
        if (isEntity(id1) and isEntity(id2)) {
            continue;
        }

        evaluated.emplace(id1, id2);

        if (isProjectile(id1) and isProjectile(id2)) {
            continue;
        }

        poly::EntityID projectile = isProjectile(id1) ? id1 : id2;
        poly::EntityID entity = isEntity(id1) ? id1 : id2;

        if (isPlayerProjectile(projectile) and isPlayer(entity)) {
            continue;
        } else if (isEnemyProjectile(projectile) and isEnemy(entity)) {
            continue;
        }

        Position& projectilePos = ecs.getData<Position>(projectile);
        auto& [entityHealth] = ecs.getData<Health>(entity);

        --entityHealth;
        ecs.markForDeletion(projectile);
        for (int i = 0; i < 5; ++i) {
            particleManager.spawnParticle(projectilePos);
        }
    }

    for (const CollisionPair& collision : evaluated) {
        collisions.erase(collision);
    }
}
