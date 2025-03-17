#include "Weapon.h"

Weapon::Weapon(const std::string& spritePath, float width, float height) {
    if (!spritePath.empty())
        this->initWithFile(spritePath);
    else {
        this->init();
        this->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
        this->setTextureRect(cocos2d::Rect(0, 0, width, height));
        this->setColor(cocos2d::Color3B::WHITE);
    }
    this->setAnchorPoint(cocos2d::Vec2(0, 0));

    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseMove = [this](cocos2d::Event* event) {
        cocos2d::EventMouse* e = (cocos2d::EventMouse*)event;
        lastMousePos = e->getLocationInView();
        lastMousePos.y = -WINDOW_HEIGHT + lastMousePos.y + this->getParent()->getPosition().y;
        lastMousePos.x = lastMousePos.x - this->getParent()->getPosition().x;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Weapon::followMouse() {
    cocos2d::Vec2 direction = this->lastMousePos;

    if (!direction.isZero()) {
        direction.normalize();
    }

    // New position
    float newX = offset * direction.x;
    float newY = offset * direction.y;
    this->setPosition(newX + 50, newY + 50);

    // Rotate
    float degrees = CC_RADIANS_TO_DEGREES(atan2(direction.y, direction.x));
    this->setRotation(-degrees);

    // Flip 
    if (direction.x < 0) {
        this->setFlippedY(true);  // Flip when left
    }
    else {
        this->setFlippedY(false);
    }
}

void Weapon::update(float dt) {
    this->followMouse();
}