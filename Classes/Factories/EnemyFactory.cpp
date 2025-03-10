#include "Factories/EnemyFactory.h"

Enemy* EnemyFactory::createEnemy(const std::string& type) {
    /*if (type == "zombie") {
        return Enemy::create("zombie.png", 100, 10);
    }
    else if (type == "robot") {
        return Enemy::create("robot.png", 200, 20);
    }*/
    return nullptr;
}
