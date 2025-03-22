#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "../Objects/Person/Enemy.h"

class EnemyFactory {
public:
    static Enemy* createEnemy(const std::string& type);
};

#endif // ENEMY_FACTORY_H
