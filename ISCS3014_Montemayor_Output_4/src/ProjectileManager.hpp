#ifndef SRC_PROJECTILEMANAGER_HPP_
#define SRC_PROJECTILEMANAGER_HPP_

#include <SFML/Graphics.hpp>

#include <Poly/EntityComponentSystem.hpp>
#include <Poly/Logging.hpp>

#include "Components.hpp"
#include "Constants.hpp"
#include "ParticleManager.hpp"
#include "Physics.hpp"
#include "ProjectileBehaviors.hpp"
#include "Player.hpp"
#include "SpriteManager.hpp"

// Manages collision and deletion of projectiles
class ProjectileManager {
public:
    ProjectileManager(poly::ECS& ecs, ParticleManager& particleManager,
        Physics& physics, Player& player, SpriteManager& spriteManager);

    void update(double deltaTime);

    void playerShoot();

    void enemyShoot(poly::EntityID enemyID);

    // iterate through all projectile types and delete if they're offscreen
    void deleteOffscreen();

    void handleCollisions();

private:
    poly::EntityID createShot(const Position& pos, const Velocity& vel,
        const sf::IntRect& spriteRect);

    poly::ECS& ecs;
    ParticleManager& particleManager;
    Physics& physics;
    Player& player;
    SpriteManager& spriteManager;
};

#endif // SRC_PROJECTILEMANAGER_HPP_
