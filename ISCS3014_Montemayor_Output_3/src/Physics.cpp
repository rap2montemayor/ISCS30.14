
#include "Physics.hpp"

// Helper function I didn't bother putting in the class.
sf::FloatRect Physics::getRect(const Position& pos, const Size& size) {
    return sf::FloatRect({pos.x, pos.y}, {size.x, size.y});
}

Physics::Physics(poly::ECS& ecs) : ecs(ecs), deltaRemaining(0) {
    poly::logInfo("Physics::Physics");
}

void Physics::update(double deltaTime) {
    deltaRemaining += deltaTime;
    const double physicsUpdate = 1./240.;
    while (deltaRemaining > physicsUpdate) {
        ecs.runSystem<Position, Velocity, Acceleration>(
            [&](poly::EntityList entities) {
                // poly::logInfo("doing physics on", entities.size(), "entities");
                move(entities, physicsUpdate);
            }
        );

        ecs.runSystem<Position, Size>(
            [&](poly::EntityList entities) {
                collisions(entities, physicsUpdate);
                // poly::logInfo("resolved", collisionPairs.size(), "collisions");
            }
        );

        deltaRemaining -= physicsUpdate;
    }
}

void Physics::move(poly::EntityList entities, double deltaTime) {
    const float eps = 0.001f;
    const float terminalVelocityX = 500.f;
    const float terminalVelocityY = 2000.f;
    for (poly::EntityID& i: entities) {
        Position& pos = ecs.getData<Position>(i);
        Velocity& vel = ecs.getData<Velocity>(i);
        Acceleration& accel = ecs.getData<Acceleration>(i);

        const auto& [collisionDirections] = ecs.getData<Collision>(i);
        const bool above = collisionDirections & Collision::Above;
        const bool below = collisionDirections & Collision::Below;
        const bool right = collisionDirections & Collision::Right;
        const bool left = collisionDirections & Collision::Left;

        if (not (left or right)) {
            vel.x += accel.x * deltaTime;
            if (abs(vel.x) < eps) {
                vel.x = 0;
            } else if (abs(vel.x) > terminalVelocityX) {
                vel.x = terminalVelocityX * (vel.x > 0 ? 1 : -1);
            }
            pos.x += vel.x * deltaTime;
        } else {
            vel.x = 0;
        }

        if (above or not below or (below and vel.y < 0)) {
            vel.y = above ? 0 : vel.y;
            vel.y += accel.y * deltaTime;
            if (abs(vel.y) < eps) {
                vel.y = 0;
            } else if (abs(vel.y) > terminalVelocityY) {
                vel.y = terminalVelocityY * (vel.y > 0 ? 1 : -1);
            }
            pos.y += vel.y * deltaTime;
        } else {
            vel.y = 0;
        }
    }
}

void Physics::collisions(poly::EntityList entities, double deltaTime) {
    collisionPairs.clear();
    for (poly::EntityID id : entities) {
        ecs.getData<Collision>(id) = {0u};
    }
    for (const poly::EntityID& id : entities) {
        if (intersecting(player, id)) {
            collisionPairs.emplace_back(player, id);
        }
    }
    // for (size_t i = 0; i < entities.size(); ++i) {
    //     const poly::EntityID& id1 = entities[i];
    //     for (size_t j = i+1; j < entities.size(); ++j) {
    //         const poly::EntityID& id2 = entities[j];
    //         if (intersecting(id1, id2)) {
    //             collisionPairs.emplace_back(id1, id2);
    //         }
    //     }
    // }
    handleCollisions(deltaTime);
}

bool Physics::intersecting(poly::EntityID id1, poly::EntityID id2) {
    const Position& pos1 = ecs.getData<Position>(id1);
    const Position& pos2 = ecs.getData<Position>(id2);
    const Size& size1 = ecs.getData<Size>(id1);
    const Size& size2 = ecs.getData<Size>(id2);
    sf::FloatRect rect1 = getRect(pos1, size1);
    sf::FloatRect rect2 = getRect(pos2, size2);
    return rect1.intersects(rect2);
}

float Physics::getIntersectionTime(poly::EntityID& id1, poly::EntityID& id2, double deltaTime) {
    const Position& pos1 = ecs.getData<Position>(id1);
    const Position& pos2 = ecs.getData<Position>(id2);

    const Size& size1 = ecs.getData<Size>(id1);
    const Size& size2 = ecs.getData<Size>(id2);

    const Velocity& vel1 = ecs.getData<Velocity>(id1);
    const Velocity& vel2 = ecs.getData<Velocity>(id2);

    // I could definitely just math this but I am lazy
    // log(n) is still pretty fast

    const float eps = 1e-3;
    float lo = -deltaTime, hi = 0, mid;
    Position newPos1 = pos1;
    Position newPos2 = pos1;
    sf::FloatRect rect1;
    sf::FloatRect rect2;
    while (hi-lo > eps) {
        mid = (hi+lo) / 2;

        newPos1 = pos1;
        newPos2 = pos2;
        newPos1.x += vel1.x * mid;
        newPos1.y += vel1.y * mid;
        newPos2.x += vel2.x * mid;
        newPos2.y += vel2.y * mid;
        rect1 = getRect(newPos1, size1);
        rect2 = getRect(newPos2, size2);

        if (rect1.intersects(rect2)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return lo;
}

bool Physics::intersectsX(poly::EntityID& id1, poly::EntityID& id2, double deltaTime) {
    Position pos1 = ecs.getData<Position>(id1);
    Position pos2 = ecs.getData<Position>(id2);

    Size& size1 = ecs.getData<Size>(id1);
    Size& size2 = ecs.getData<Size>(id2);

    Velocity& vel1 = ecs.getData<Velocity>(id1);
    Velocity& vel2 = ecs.getData<Velocity>(id2);

    pos1.x += vel1.x * deltaTime;
    pos2.x += vel2.x * deltaTime;
    sf::FloatRect rect1 = getRect(pos1, size1);
    sf::FloatRect rect2 = getRect(pos2, size2);
    return rect1.intersects(rect2);
}

bool Physics::intersectsY(poly::EntityID& id1, poly::EntityID& id2, double deltaTime) {
    Position pos1 = ecs.getData<Position>(id1);
    Position pos2 = ecs.getData<Position>(id2);
    
    Size& size1 = ecs.getData<Size>(id1);
    Size& size2 = ecs.getData<Size>(id2);

    Velocity& vel1 = ecs.getData<Velocity>(id1);
    Velocity& vel2 = ecs.getData<Velocity>(id2);

    pos1.y += vel1.y * deltaTime;
    pos2.y += vel2.y * deltaTime;

    sf::FloatRect rect1 = getRect(pos1, size1);
    sf::FloatRect rect2 = getRect(pos2, size2);
    return rect1.intersects(rect2);
}

void Physics::setCollisionX(poly::EntityID id1, poly::EntityID id2) {
    Position& pos1 = ecs.getData<Position>(id1);
    Position& pos2 = ecs.getData<Position>(id2);
    Size& size1 = ecs.getData<Size>(id1);
    Size& size2 = ecs.getData<Size>(id2);

    auto& [collision1] = ecs.getData<Collision>(id1);
    auto& [collision2] = ecs.getData<Collision>(id2);

    // to avoid snagging
    sf::FloatRect rect1 = getRect(pos1, size1);
    sf::FloatRect rect2 = getRect(pos2, size2);
    sf::FloatRect intersect;
    rect1.intersects(rect2, intersect);

    if (intersect.height < 5) {
        return;
    } else if (pos1.x < pos2.x) {
        collision1 |= Collision::Right;
        collision2 |= Collision::Left;
    } else {
        collision1 |= Collision::Left;
        collision2 |= Collision::Right;
    }
}

void Physics::setCollisionY(poly::EntityID id1, poly::EntityID id2) {
    Position& pos1 = ecs.getData<Position>(id1);
    Position& pos2 = ecs.getData<Position>(id2);

    auto& [collision1] = ecs.getData<Collision>(id1);
    auto& [collision2] = ecs.getData<Collision>(id2);

    if (pos1.y < pos2.y) {
        collision1 |= Collision::Below;
        collision2 |= Collision::Above;
    } else {
        collision1 |= Collision::Above;
        collision2 |= Collision::Below;
    }
}

void Physics::handleCollisions(double deltaTime) {
    for (auto& [id1, id2] : collisionPairs) {
        if (not intersecting(id1, id2)) {
            continue;
        }

        float intersectTime = getIntersectionTime(id1, id2, deltaTime);
        bool intersectx = intersectsX(id1, id2, intersectTime);

        Position& pos1 = ecs.getData<Position>(id1);
        Velocity& vel1 = ecs.getData<Velocity>(id1);

        Position& pos2 = ecs.getData<Position>(id2);
        Velocity& vel2 = ecs.getData<Velocity>(id2);

        // If pushing along the x axis undoes the collision, commit to it
        if (not intersectx) {
            setCollisionX(id1, id2);
            pos1.x += vel1.x * intersectTime;
            pos2.x += vel2.x * intersectTime;
        }
    }

    for (auto& [id1, id2] : collisionPairs) {
        if (not intersecting(id1, id2)) {
            continue;
        }

        float intersectTime = getIntersectionTime(id1, id2, deltaTime);
        bool intersecty = intersectsY(id1, id2, intersectTime);

        Position& pos1 = ecs.getData<Position>(id1);
        Velocity& vel1 = ecs.getData<Velocity>(id1);

        Position& pos2 = ecs.getData<Position>(id2);
        Velocity& vel2 = ecs.getData<Velocity>(id2);

        // If pushing along the y axis undoes the collision, commit to it
        if (not intersecty) {
            setCollisionY(id1, id2);
            pos1.y += vel1.y * (intersectTime - 0.001); // to avoid snagging
            pos2.y += vel2.y * (intersectTime - 0.001); 
        }
    }
}

