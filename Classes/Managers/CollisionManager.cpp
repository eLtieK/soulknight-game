﻿#include "CollisionManager.h"
#include "../Scenes/GameScene.h"
#include "../Objects/Weapon/Gun.h"
#include "../Objects/Weapon/Sword.h"
#include "../Objects/Item/Item.h"
#include "../Objects/Item/Jar.h"
#include "../Objects/Item/Coin.h"
#include "../Objects/Person/Enemy.h"
#include "../Objects/Person/Boss.h"
#include "../Factories/ItemFactory.h"
#include "EffectManager.h"
#include "SoundManager.h"

bool CollisionManager::checkCollisionWithRects(Person* person) {
    //Boss
    if (dynamic_cast<Boss*>(person)) return false;

    std::vector<cocos2d::Rect> collisionRects = GameScene::getCollisions();

    // Log vị trí của person
    cocos2d::Rect personRect = person->getBoundingBox();

    for (const auto& rect : collisionRects) {
        if (personRect.intersectsRect(rect)) {
            return true; // Có va chạm
        }
    }
    return false; // Không có va chạm
}

void CollisionManager::checkCollisionWithWeapon(Weapon* weapon, std::vector<Bullet*>& bullets, std::vector<cocos2d::Sprite*>& sprites) {
    if (dynamic_cast<Gun*>(weapon)) {
        CollisionManager::checkCollisionsBullet(bullets, sprites);
    }
    else if (dynamic_cast<Sword*>(weapon)) {
        CollisionManager::checkCollisionsSword(weapon, sprites);
    }
}

void CollisionManager::checkCollisionsSword(Weapon* weapon, std::vector<cocos2d::Sprite*>& sprites) {
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
    for (auto itSprite = sprites.begin(); itSprite != sprites.end(); ) {
        cocos2d::Sprite* sprite = *itSprite;

        if (weaponRect.intersectsRect(sprite->getBoundingBox())) {
            CCLOG("Sword hit Enemy! Enemy Removed");
            if (dynamic_cast<Enemy*>(sprite)) {
                EffectManager::playBleedEffect(sprite->getParent(), sprite->getPosition());
                if (!dynamic_cast<Boss*>(sprite)) GameManager::getInstance()->setEnemyLeft(-1);
                SoundManager::playBleed();
                SoundManager::playSword();
            }
            if (dynamic_cast<Jar*>(sprite)) {
                SoundManager::playJar();
                SoundManager::playSword();
                EffectManager::playSmokeEffect(sprite->getParent(), sprite->getPosition());

                //Add coin
                Item* item = ItemFactory::createItem("coin");
                item->setPosition(cocos2d::Vec2(sprite->getPosition()));
                sprite->getParent()->addChild(item, 1);
                sprites.push_back(item);
            }

            // Xóa Enemy
            if (dynamic_cast<Boss*>(sprite)) {
                ++itSprite; //Boss cant kill with sword
            }
            else {
                if (dynamic_cast<Coin*>(sprite))  ++itSprite;
                else {
                    sprite->removeFromParentAndCleanup(true);
                    itSprite = sprites.erase(itSprite);
                }
            }
        }
        else {
            ++itSprite;
        }
    }
}

void CollisionManager::checkCollisionsBullet(std::vector<Bullet*>& bullets, std::vector<cocos2d::Sprite*>& sprites) {
    for (auto itBullet = bullets.begin(); itBullet != bullets.end(); ) {
        Bullet* bullet = *itBullet;
        auto bulletPos = bullet->getPosition() + bullet->getParent()->getPosition();
        auto bulletBox = bullet->getBoundingBox();
        auto bulletRect = cocos2d::Rect(bulletPos, bulletBox.size);
       
        /*CCLOG("Bullet Rect: (%.2f, %.2f, %.2f, %.2f)",
            bulletRect.origin.x, bulletRect.origin.y,
            bulletRect.size.width, bulletRect.size.height);*/

        bool bulletHit = false;
        for (auto itSprite = sprites.begin(); itSprite != sprites.end(); ) {
            cocos2d::Sprite* sprite = *itSprite;

            /*CCLOG("Enemy Pos: (%.2f, %.2f)", enemy->getPosition().x, enemy->getPosition().y);
            CCLOG("Enemy Size: (%.2f, %.2f)", enemy->getBoundingBox().size.width, enemy->getBoundingBox().size.height);*/


            if (bulletRect.intersectsRect(sprite->getBoundingBox())) {
                CCLOG("Bullet hit Enemy! Enemy Removed");

                // Xóa Enemy
                if (dynamic_cast<Enemy*>(sprite)) {
                    EffectManager::playBleedEffect(sprite->getParent(), sprite->getPosition());
                    SoundManager::playBleed();
                    if (!dynamic_cast<Boss*>(sprite)) GameManager::getInstance()->setEnemyLeft(-1);
                }
                if (dynamic_cast<Jar*>(sprite)) {
                    EffectManager::playSmokeEffect(sprite->getParent(), sprite->getPosition());
                    SoundManager::playJar();
                    Item* item = ItemFactory::createItem("coin");
                    item->setPosition(cocos2d::Vec2(sprite->getPosition()));
                    sprite->getParent()->addChild(item, 1);
                    sprites.push_back(item);
                }

                bulletHit = true;

                if (dynamic_cast<Boss*>(sprite)) {
                    Boss* boss = dynamic_cast<Boss*>(sprite);
                    boss->onHit();
                    if (boss->isDefeated()) {
                        sprite->removeFromParentAndCleanup(true);
                        itSprite = sprites.erase(itSprite);
                        GameManager::getInstance()->setEnemyLeft(-1);
                    }
                    else ++itSprite;
                }
                else {
                    if (dynamic_cast<Coin*>(sprite))  ++itSprite;
                    else {
                        sprite->removeFromParentAndCleanup(true);
                        itSprite = sprites.erase(itSprite);
                    }
                }
            }
            else {
                ++itSprite;
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

bool CollisionManager::checkCollisionWithPlayer(Player* player, std::vector<cocos2d::Sprite*>& sprites) {
    // Log vị trí của person
    cocos2d::Rect playerRect = player->getBoundingBox();

    for (auto it = sprites.begin(); it != sprites.end(); ) {
        cocos2d::Sprite* sprite = *it;
        if (playerRect.intersectsRect(sprite->getBoundingBox())) {
            if (dynamic_cast<Coin*>(sprite)) {
                sprite->removeFromParentAndCleanup(true);
                it = sprites.erase(it);  // Xóa phần tử an toàn
                GameManager::getInstance()->setCoins(1);
                SoundManager::playGold();
            }
            else {
                ++it;
            }
            return true; // Có va chạm
        }
        else {
            ++it;
        }
    }
    return false; // Không có va chạm
}
