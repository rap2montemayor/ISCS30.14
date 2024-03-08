#include "EnemyBehaviors.hpp"

EnemyBehavior::EnemyBehavior() : shotCooldown(0), fire(0),
    behaviorCallback(nullptr) {}

void EnemyBehavior::update(double deltaTime) {
    behaviorCallback(*this, deltaTime);
}

void EnemyBehavior::shootUpdate(EnemyBehavior& self, double deltaTime) {
    self.shotCooldown -= deltaTime;
    while (self.shotCooldown < 0) {
        self.shotCooldown += 0.5;
        ++self.fire;
    }
}

void EnemyBehavior::noUpdate(EnemyBehavior&, double) {}
