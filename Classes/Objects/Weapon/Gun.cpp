#include "Gun.h"
#include "../Person/Player.h"

Gun::Gun(const std::string& spritePath) : Weapon(spritePath) {
    
}

void Gun::attack() {
    cocos2d::Vec2 direction = this->lastMousePos;

    if (!direction.isZero()) {
        direction.normalize();
    }

    float width = 20; float height = 20;

    Bullet* bullet = new Bullet("", width, height, direction);
    if (bullet) {
        this->getParent()->getParent()->addChild(bullet);

        // get position 
        float angleRad = CC_DEGREES_TO_RADIANS(this->getRotation());
        float offsetX = cos(angleRad);
        float offsetY = sin(angleRad);
        cocos2d::Vec2 position = this->getParent()->convertToWorldSpace(this->getPosition()) + cocos2d::Vec2(offsetX, offsetY);
        float newX = position.x + 10;
        float newY = position.y + 10;
        bullet->setPosition(newX, newY);

    }
}