#include "CollisionManager.h"
#include "../Scenes/GameScene.h"
#include "../Objects/Weapon/Gun.h"
#include "../Objects/Weapon/Sword.h"

bool CollisionManager::checkCollisionWithRects(Person* person) {
    std::vector<cocos2d::Rect> collisionRects = GameScene::getCollisions();

    // Log vị trí của person
    cocos2d::Rect personRect = person->getBoundingBox();
    /*CCLOG("Person Position: (%.2f, %.2f) - Size: (%.2f x %.2f)",
        personRect.origin.x, personRect.origin.y,
        personRect.size.width, personRect.size.height);*/

    for (const auto& rect : collisionRects) {
       /* CCLOG("Collision Rect: (%.2f, %.2f) - Size: (%.2f x %.2f)",
            rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);*/

        // Kiểm tra va chạm
        if (personRect.intersectsRect(rect)) {
            //CCLOG("Collision detected!");
            return true; // Có va chạm
        }
    }
    return false; // Không có va chạm
}

void CollisionManager::checkCollisionWithWeapon(Weapon* weapon, std::vector<Bullet*>& bullets, std::vector<Enemy*>& enemies) {
    if (dynamic_cast<Gun*>(weapon)) {
        CollisionManager::checkCollisionsBullet(bullets, enemies);
    }
    else if (dynamic_cast<Sword*>(weapon)) {
        CollisionManager::checkCollisionsSword(weapon, enemies);
    }
}

void CollisionManager::checkCollisionsSword(Weapon* weapon, std::vector<Enemy*>& enemies) {
    auto weaponPos = weapon->getPosition() + weapon->getParent()->getPosition();
    cocos2d::Size weaponSize = weapon->getContentSize();
    float weaponRotation = -CC_DEGREES_TO_RADIANS(weapon->getRotation()); // Đổi độ sang radian

    // Tính bốn đỉnh sau khi xoay
    cocos2d::Vec2 center = weaponPos;
    cocos2d::Vec2 topLeft = center + cocos2d::Vec2(-weaponSize.width / 2, weaponSize.height / 2).rotateByAngle(cocos2d::Vec2::ZERO, weaponRotation);
    cocos2d::Vec2 topRight = center + cocos2d::Vec2(weaponSize.width / 2, weaponSize.height / 2).rotateByAngle(cocos2d::Vec2::ZERO, weaponRotation);
    cocos2d::Vec2 bottomLeft = center + cocos2d::Vec2(-weaponSize.width / 2, -weaponSize.height / 2).rotateByAngle(cocos2d::Vec2::ZERO, weaponRotation);
    cocos2d::Vec2 bottomRight = center + cocos2d::Vec2(weaponSize.width / 2, -weaponSize.height / 2).rotateByAngle(cocos2d::Vec2::ZERO, weaponRotation);

    // Tìm min-max để tạo bounding box mới
    float minX = std::min({ topLeft.x, topRight.x, bottomLeft.x, bottomRight.x });
    float maxX = std::max({ topLeft.x, topRight.x, bottomLeft.x, bottomRight.x });
    float minY = std::min({ topLeft.y, topRight.y, bottomLeft.y, bottomRight.y });
    float maxY = std::max({ topLeft.y, topRight.y, bottomLeft.y, bottomRight.y });

    // Tạo bounding box mới
    cocos2d::Rect weaponRect(minX, minY, maxX - minX, maxY - minY);
    for (auto itEnemy = enemies.begin(); itEnemy != enemies.end(); ) {
        Enemy* enemy = *itEnemy;

        if (weaponRect.intersectsRect(enemy->getBoundingBox())) {
            CCLOG("Sword hit Enemy! Enemy Removed");

            // Xóa Enemy
            enemy->removeFromParentAndCleanup(true);
            itEnemy = enemies.erase(itEnemy);

        }
        else {
            ++itEnemy;
        }
    }
}

void CollisionManager::checkCollisionsBullet(std::vector<Bullet*>& bullets, std::vector<Enemy*>& enemies) {
    for (auto itBullet = bullets.begin(); itBullet != bullets.end(); ) {
        Bullet* bullet = *itBullet;
        auto bulletPos = bullet->getPosition() + bullet->getParent()->getPosition();
        auto bulletBox = bullet->getBoundingBox();
        auto bulletRect = cocos2d::Rect(bulletPos, bulletBox.size);
       
        /*CCLOG("Bullet Rect: (%.2f, %.2f, %.2f, %.2f)",
            bulletRect.origin.x, bulletRect.origin.y,
            bulletRect.size.width, bulletRect.size.height);*/

        bool bulletHit = false;
        for (auto itEnemy = enemies.begin(); itEnemy != enemies.end(); ) {
            Enemy* enemy = *itEnemy;

            /*CCLOG("Enemy Pos: (%.2f, %.2f)", enemy->getPosition().x, enemy->getPosition().y);
            CCLOG("Enemy Size: (%.2f, %.2f)", enemy->getBoundingBox().size.width, enemy->getBoundingBox().size.height);*/


            if (bulletRect.intersectsRect(enemy->getBoundingBox())) {
                CCLOG("Bullet hit Enemy! Enemy Removed");

                // Xóa Enemy
                enemy->removeFromParentAndCleanup(true);
                itEnemy = enemies.erase(itEnemy);

                bulletHit = true;
            }
            else {
                ++itEnemy;
            }
        }

        // Nếu bullet đã va chạm thì xóa khỏi danh sách
        if (bulletHit) {
            bullet->removeFromParentAndCleanup(true);
            itBullet = bullets.erase(itBullet);
        }
        else {
            ++itBullet;
        }
    }
}
