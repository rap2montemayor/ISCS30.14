#ifndef SRC_PROJECTILEBEHAVIORS_HPP_
#define SRC_PROJECTILEBEHAVIORS_HPP_

#include "Components.hpp"
#include "Math.hpp"

struct ProjectileBehavior {
    ProjectileBehavior();
    void start();
    void update(double deltaTime);
    void setPositionPtr(Position* pos);
    void setVelocityPtr(Velocity* vel);
    void updateTargetPos(const Position& targetPos);

    Position* pos;
    Velocity* vel;
    Position targetPos;

    std::function<void(ProjectileBehavior&)> spawnBehavior;
    std::function<void(ProjectileBehavior&, double)> updateBehavior;

    static void defaultSpawn(ProjectileBehavior&);
    static void defaultUpdate(ProjectileBehavior&, double deltaTime);
    static void aimedSpawn(ProjectileBehavior&);
};




#endif // SRC_PROJECTILEBEHAVIORS_HPP_W