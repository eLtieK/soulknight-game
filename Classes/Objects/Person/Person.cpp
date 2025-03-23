#include "Person.h"
#include "../../Managers/CollisionManager.h"
#include "../../Utils/loader.h"

Person::Person(const std::string& spritePath , float x, float y, float width, float height, float speed) {
    this->x = x; this->y = y;
    this->width = width; this->height = height;
    this->speed = speed;
    
    if (!spritePath.empty())
        this->initWithFile(spritePath);
    else {
        this->init();
        this->setTextureRect(cocos2d::Rect(0, 0, this->width, this->height));
        this->setColor(cocos2d::Color3B::WHITE);
    }
}

Person::~Person() {
    // Giải phóng bộ nhớ của các animation nếu chúng tồn tại
    if (animUp) {
        animUp->release();
        animUp = nullptr;
    }
    if (animDown) {
        animDown->release();
        animDown = nullptr;
    }
    if (animLeft) {
        animLeft->release();
        animLeft = nullptr;
    }
    if (animRight) {
        animRight->release();
        animRight = nullptr;
    }

    // Nếu đang chạy animation, dừng lại
    if (animateAction) {
        this->stopAction(animateAction);
        animateAction = nullptr;
    }
}


void Person::setPosition(const cocos2d::Vec2& pos) {
    this->x = pos.x; this->y = pos.y;
    cocos2d::Sprite::setPosition(pos);
}

void Person::move(float dt) {
    float dx = 0, dy = 0;
    float oldX = x, oldY = y;
    if (this->direction_left) dx -= 1;
    if (this->direction_right) dx += 1;
    if (this->direction_down) dy -= 1;
    if (this->direction_up) dy += 1;

    int length = (dx * dx + dy * dy);
    if (length == 2) { //normalize
        dx /= (float)std::sqrt(length);
        dy /= (float)std::sqrt(length);
    }

    this->x += dx * this->speed * dt;
    this->y += dy * this->speed * dt;

    this->setPosition(cocos2d::Vec2(x, y));
    if (CollisionManager::checkCollisionWithRects(this)) {
        this->x = oldX;
        this->y = oldY;
        this->setPosition(cocos2d::Vec2(x, y));
    }

}

void Person::update(float dt) {
    move(dt);
    updateAnimation();
}

void Person::updateAnimation() {
    if (animateAction == nullptr) {
        if (direction_up && direction_down) { }
        else if (direction_left && direction_right) { }
        else if (direction_left && (direction_up || direction_down)) {
            /*animateAction = cocos2d::Animate::create(animLeft);
            this->runAction(animateAction);*/
        }
        else if (direction_right && (direction_up || direction_down)) {
            /*animateAction = cocos2d::Animate::create(animRight);
            this->runAction(animateAction);*/
        }
        else if (direction_up) {
            animateAction = cocos2d::Animate::create(animUp);
            this->runAction(animateAction);
        }
        else if (direction_down) {
            animateAction = cocos2d::Animate::create(animDown);
            this->runAction(animateAction);
        }
        else if (direction_left) {
            animateAction = cocos2d::Animate::create(animLeft);
            this->runAction(animateAction);
        }
        else if (direction_right) {
            animateAction = cocos2d::Animate::create(animRight);
            this->runAction(animateAction);
        }
    }
    else {
        if (direction_up && direction_down) { this->stopAllActions(); }
        else if (direction_left && direction_right) { this->stopAllActions(); }
        else if (direction_left && (direction_up || direction_down)) {

        }
        else if (direction_right && (direction_up || direction_down)) {

        }
        else if (direction_left && animateAction->getAnimation() != animLeft) {
            this->stopAllActions();
            animateAction = cocos2d::Animate::create(animLeft);
            this->runAction(animateAction);
        }
        else if (direction_right && animateAction->getAnimation() != animRight) {
            this->stopAllActions();
            animateAction = cocos2d::Animate::create(animRight);
            this->runAction(animateAction);
        }
        else if (direction_up && animateAction->getAnimation() != animUp) {
            this->stopAllActions();
            animateAction = cocos2d::Animate::create(animUp);
            this->runAction(animateAction);
        }
        else if (direction_down && animateAction->getAnimation() != animDown) {
            this->stopAllActions();
            animateAction = cocos2d::Animate::create(animDown);
            this->runAction(animateAction);
        }
    }
}
