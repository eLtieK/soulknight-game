#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "cocos2d.h"
#include "../Objects/Person/Enemy.h"
#include "../Objects/Person/Player.h"
#include "../Objects/Weapon/Bullet.h"
#include "../Objects/Item/Item.h"

class CollisionManager {
public:
    static void checkCollisionWithWeapon(Weapon* weapon, std::vector<Bullet*>& bullets, std::vector<cocos2d::Sprite*>& sprites);
    static void checkCollisionsSword(Weapon* weapon, std::vector<cocos2d::Sprite*>& sprites);
    static void checkCollisionsBullet(std::vector<Bullet*>& bullets, std::vector<cocos2d::Sprite*>& sprites);
    static bool checkCollisionWithRects(Person* person);
    static bool checkCollisionWithPlayer(Player* player, std::vector<cocos2d::Sprite*>& sprites);
};

#endif
