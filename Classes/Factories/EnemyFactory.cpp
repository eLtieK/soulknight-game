#include "Factories/EnemyFactory.h"

Enemy* EnemyFactory::createEnemy(const std::string& type) {
    if (type == "boss") {
        return new Boss();
    }
    return new Enemy();
}
