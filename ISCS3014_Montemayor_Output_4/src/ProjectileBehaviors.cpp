#include "ProjectileBehaviors.hpp"

ProjectileBehavior::ProjectileBehavior()
    : spawnBehavior(defaultSpawn), updateBehavior(defaultUpdate) {}

void ProjectileBehavior::start() {
    if (spawnBehavior != nullptr) {
        spawnBehavior(*this);
    }
}

void ProjectileBehavior::update(double deltaTime) {
    if (updateBehavior != nullptr) {
        updateBehavior(*this, deltaTime);
    }
}

void ProjectileBehavior::defaultSpawn(ProjectileBehavior&) {}
void ProjectileBehavior::defaultUpdate(ProjectileBehavior&, double) {}
void ProjectileBehavior::aimedSpawn(ProjectileBehavior& self) {
    sf::Vector2f totarget = self.targetPos - *self.pos;
    normalize(totarget);
    totarget *= getLength(*self.vel);
    *self.vel = {totarget.x, totarget.y};
}
