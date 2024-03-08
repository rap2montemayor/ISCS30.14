#include "Player.hpp"

Player::Player(poly::ECS& ecs, Controller& controller,
    ParticleManager& particleManager, SpriteManager& spriteManager)
    : ecs(ecs), controller(controller), particleManager(particleManager),
    spriteManager(spriteManager), shotCooldown(0), fire(0), dead(false) {}

void Player::init() {
    id = ecs.createEntity();
    ecs.setData<EntityType>(id, {EntityType::Player});
    ecs.setData<Health>(id, {5});
    ecs.setData<Position>(id, {200, 200});
    ecs.setData<Radius>(id, {5});
    ecs.setData<Size>(id, {50, 50});
    ecs.setData<Velocity>(id, {0, 0});
    ecs.setData<Sprite>(id, {
        spriteManager.getSpriteSheet(),
        spriteManager.getSpriteRect(spriteManager.getSpriteID("Reimu"))
    });
}

void Player::update(double deltaTime) {
    if (dead) return;

    const double shotInterval = 0.1;
    shotCooldown -= deltaTime;
    while (shotCooldown < 0) {
        shotCooldown += shotInterval;
        if (controller.isPressed(InputState::Shoot)) {
            ++fire;
        }
    }

    Position& pos = ecs.getData<Position>(id);
    pos.x = std::clamp(pos.x, playfieldLeft+25, playfieldRight-25);
    pos.y = std::clamp(pos.y, playfieldTop+25, playfieldBottom-25);

    auto& [health] = ecs.getData<Health>(id);
    if (health <= 0) {
        dead = true;
        particleManager.spawnExplosion(pos);
        ecs.setData<Size>(id, {0, 0});
        ecs.setData<Position>(id, {-100, -100});
    }
}

void Player::processInput() {
    if (dead) return;

    Velocity& vel = ecs.getData<Velocity>(id);

    const bool up    = controller.isPressed(InputState::Up);
    const bool down  = controller.isPressed(InputState::Down);
    const bool left  = controller.isPressed(InputState::Left);
    const bool right = controller.isPressed(InputState::Right);

    const float speed = 500.f;
    const float diag = speed / std::sqrt(2);

    std::pair<bool, std::function<void()>> mappings[] = {
        {up,                  [&] { vel.y = -speed; }},
        {down,                [&] { vel.y =  speed; }},
        {left,                [&] { vel.x = -speed; }},
        {right,               [&] { vel.x =  speed; }},
        {up and left,         [&] { vel.y = -diag; vel.x = -diag; }},
        {up and right,        [&] { vel.y = -diag; vel.x =  diag; }},
        {down and left,       [&] { vel.y =  diag; vel.x = -diag; }},
        {down and right,      [&] { vel.y =  diag; vel.x =  diag; }},
        {not (left or right), [&] { vel.x = 0; }},
        {not (up or down),    [&] { vel.y = 0; }},
    };

    for (auto& [condition, callback] : mappings) {
        if (condition) {
            callback();
        }
    }
}

poly::EntityID Player::getID() {
    return id;
}

int& Player::getFire() {
    return fire;
}

bool Player::isDead() {
    return dead;
}
