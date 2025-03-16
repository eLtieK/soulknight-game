#include "Person.h"

Person::Person(const std::string& spritePath , float x, float y, float width, float height, float speed) {
    this->x = x; this->y = y;
    this->width = width; this->height = height;
    this->speed = speed;
    
    if (!spritePath.empty())
        this->initWithFile(spritePath);
    else {
        this->init();
        this->setTextureRect(cocos2d::Rect(this->x, this->y, this->width, this->height));
        this->setColor(cocos2d::Color3B::WHITE);
    }
}

void Person::move(float dt) {
    float dx = 0, dy = 0;
    if (this->direction_left) dx -= 1;
    if (this->direction_right) dx += 1;
    if (this->direction_down) dy -= 1;
    if (this->direction_up) dy += 1;

    int length = (dx * dx + dy * dy);
    if (length == 2) { //normalize
        dx /= std::sqrt(length);
        dy /= std::sqrt(length);
    }

    this->x += dx * this->speed * dt;
    this->y += dy * this->speed * dt;

    this->setPosition(cocos2d::Vec2(x, y));
}

void Person::update(float dt) {
    move(dt);
}
