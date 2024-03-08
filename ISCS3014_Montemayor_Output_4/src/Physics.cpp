#include "Physics.hpp"

Physics::Physics(poly::ECS& ecs) : ecs(ecs), deltaRemaining(0) {
    poly::logInfo("Physics::Physics");
}

void Physics::update(double deltaTime) {
    const double physicsUpdate = 1./240.;

    deltaRemaining += deltaTime;
    while (deltaRemaining >= physicsUpdate) {
        ecs.runSystem<Velocity, Acceleration>(
            [&](poly::EntityList& entities) {
                accelerate(entities, physicsUpdate);
            }
        );

        ecs.runSystem<Position, Velocity>(
            [&](poly::EntityList& entities) {
                move(entities, physicsUpdate);
            }
        );

        ecs.runSystem<Position, Radius>(
            [&](poly::EntityList& entities) {
                checkCollisions(entities);
            }
        );

        deltaRemaining -= physicsUpdate;
    }
}

void Physics::accelerate(poly::EntityList& entities, double deltaTime) {
    for (poly::EntityID& i: entities) {
        sf::Vector2f& vel = ecs.getData<Velocity>(i);
        sf::Vector2f& accel = ecs.getData<Acceleration>(i);
        vel += accel * (float) deltaTime;
    }
}

void Physics::move(poly::EntityList& entities, double deltaTime) {
    for (poly::EntityID& i: entities) {
        sf::Vector2f& pos = ecs.getData<Position>(i);
        sf::Vector2f& vel = ecs.getData<Velocity>(i);
        pos += vel * (float) deltaTime;
    }
}

template <typename T>
using Grid = std::vector<std::vector<T>>;

void Physics::checkCollisions(poly::EntityList& entities) {
    collisions.clear();
    collisions.reserve(1024);

    static poly::EntityList enemyBullets;
    static poly::EntityList playerBullets;
    static poly::EntityList enemies;
    poly::EntityID player;

    enemyBullets.clear();
    playerBullets.clear();
    enemies.clear();
    enemyBullets.reserve(1024);
    playerBullets.reserve(1024);
    enemies.reserve(1024);

    for (poly::EntityID& id : entities) {
        if (ecs.hasData<ProjectileType>(id)) {
            if (ecs.getData<ProjectileType>(id).type == ProjectileType::Enemy) {
                enemyBullets.push_back(id);
            } else {
                playerBullets.push_back(id);
            }
        } else if (ecs.hasData<EntityType>(id)) {
            if (ecs.getData<EntityType>(id).type == EntityType::Enemy) {
                enemies.push_back(id);
            } else {
                player = id;
            }
        }
    }

    auto isColliding = [&](const poly::EntityID& id1, const poly::EntityID& id2) {
        sf::Vector2f& pos1 = ecs.getData<Position>(id1);
        sf::Vector2f& pos2 = ecs.getData<Position>(id2);
        auto& [rad1] = ecs.getData<Radius>(id1);
        auto& [rad2] = ecs.getData<Radius>(id2);
        return std::hypot(pos1.x-pos2.x, pos1.y-pos2.y) <= rad1+rad2;
    };

    for (poly::EntityID& id : enemyBullets) {
        if (isColliding(player, id)) {
            collisions.emplace(player, id);
        }
    }

    for (poly::EntityID& id : enemies) {
        if (isColliding(player, id)) {
            collisions.emplace(player, id);
        }
    }

    // playerbullets - enemies will need to be slightly smarter

    // grid partitioning
    // cells are roughly 100px
    const int rows = 7;
    const int cols = 12;

    const double height = 720. / rows;
    const double width = 1280. / cols;

    static Grid<poly::EntityList> grid;

    grid.resize(rows);
    for (auto& row : grid) {
        row.resize(cols);
        for (auto& cell : row) {
            cell.clear();
            cell.reserve(128);
        }
    }

    auto placeInGrid = [&](poly::EntityID& id) {
        const auto& [x, y] = ecs.getData<Position>(id);
        const auto& [rad] = ecs.getData<Radius>(id);

        const int top = std::floor((y-rad) / height);
        const int left = std::floor((x-rad) / width);
        const int bottom = std::floor((y+rad) / height);
        const int right = std::floor((x+rad) / width);

        for (int i = std::max(0, top); i < std::min(rows, bottom+1); ++i) {
            for (int j = std::max(0, left); j < std::min(cols, right+1); ++j) {
                grid[i][j].push_back(id);
            }
        }
    };

    for (poly::EntityID& id : enemies) {
        placeInGrid(id);
    }

    for (poly::EntityID& id : playerBullets) {
        placeInGrid(id);
    }

    // casual abuse of syntax
    for (auto& row : grid) for (auto& cell : row) {
        for (auto& id1 : cell) for (auto& id2 : cell) {
            if (id1 == id2) {
                continue;
            }
            if (isColliding(id1, id2)) {
                collisions.emplace(id1, id2);
            }
        }
    }
}

std::unordered_set<CollisionPair>& Physics::getCollisions() {
    return collisions;
}
