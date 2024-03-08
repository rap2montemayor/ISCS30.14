#ifndef SRC_ENEMYBEHAVIORS_HPP_
#define SRC_ENEMYBEHAVIORS_HPP_

#include <functional>

struct EnemyBehavior {
    EnemyBehavior();
    void update(double deltaTime);

    double shotCooldown;
    int fire;
    std::function<void(EnemyBehavior&, double)> behaviorCallback;

    static void shootUpdate(EnemyBehavior& self, double deltaTime);
    static void noUpdate(EnemyBehavior& self, double deltaTime);
};

#endif // SRC_ENEMYBEHAVIORS_HPP_
