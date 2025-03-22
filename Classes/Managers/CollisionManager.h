#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "cocos2d.h"
#include "../Objects/Person/Enemy.h"
#include "../Objects/Person/Player.h"
#include "../Objects/Weapon/Bullet.h"

class CollisionManager {
public:
    static void checkCollisionWithWeapon(Weapon* weapon, std::vector<Bullet*>& bullets, std::vector<Enemy*>& enemies);
    static void checkCollisionsSword(Weapon* weapon, std::vector<Enemy*>& enemies);
    static void checkCollisionsBullet(std::vector<Bullet*>& bullets, std::vector<Enemy*>& enemies);
    static bool checkCollisionWithRects(Person* person);
};

#endif
