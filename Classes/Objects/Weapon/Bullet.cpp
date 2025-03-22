#include "Bullet.h"
#include "../../Scenes/GameScene.h"

Bullet::Bullet(const std::string& spritePath, float width, float height, cocos2d::Vec2 direction, float speed) {
    this->speed = speed;
    this->direction = direction;

    if (!spritePath.empty())
        this->initWithFile(spritePath);
    else {
        this->init();
        this->setTextureRect(cocos2d::Rect(0, 0, width, height));
        this->setColor(cocos2d::Color3B::WHITE);
    }
    this->scheduleUpdate();
}

void Bullet::update(float dt) {
    this->setPosition(this->getPosition() + direction * speed * dt);

    // Delete
    if (this->getPositionX() < 0 || this->getPositionX() > WINDOW_WIDTH ||
        this->getPositionY() < 0 || this->getPositionY() > WINDOW_HEIGHT) {

        /*CCLOG("DELETE");*/
        GameScene* gameScene = dynamic_cast<GameScene*>(this->getParent());
        if (gameScene) {
            gameScene->removeBullet(this);
        }
    }
}
