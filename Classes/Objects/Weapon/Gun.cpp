#include "Gun.h"
#include "../Person/Player.h"
#include "../../Scenes/GameScene.h"

const char* BULLET_PATH = "images/items/bullet.png";

Gun::Gun(const std::string& spritePath) : Weapon(spritePath) {
    
}

void Gun::attack() {
    cocos2d::Vec2 direction = this->lastMousePos - (cocos2d::Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

    if (!direction.isZero()) {
        direction.normalize();
    }

    float width = 20; float height = 20;

    Bullet* bullet = new Bullet(BULLET_PATH, width, height, direction);
    if (bullet) {
        this->getParent()->addChild(bullet);

        // get position 
        float angleRad = CC_DEGREES_TO_RADIANS(this->getRotation());
        float offsetX = cos(angleRad);
        float offsetY = sin(angleRad);
        float newX = direction.x * 100 + 50;
        float newY = direction.y * 100 + 50;
        bullet->setPosition(newX, newY);

        // Thêm Bullet vào danh sách trong GameScene
        GameScene* gameScene = dynamic_cast<GameScene*>(this->getParent()->getParent());
        if (gameScene) {
            gameScene->addBullets(bullet);
        }
    }
}