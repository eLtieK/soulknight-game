#ifndef ENEMY_H
#define ENEMY_H

#include "Person.h"


class Enemy : public Person {
public:
    Enemy(const std::string& spritePath = "");
    void update(float dt) override;
    void onCollision(Person* other) override;
    void move(float dt) override;
    void initAnimations() override;
    void setAnimation(cocos2d::Vec2 direction);
};

#endif // ENEMY_H
