#ifndef PERSON_H
#define PERSON_H

#include "cocos2d.h"
#include "../../Utils/loader.h"

class Person : public cocos2d::Sprite {
public:
    Person(const std::string& spritePath = "", float x = WINDOW_WIDTH / 2, float y = WINDOW_HEIGHT / 2, float width = 50, float height = 50, float speed = 500);
    /*virtual ~Person() = 0;*/

    virtual void initAnimations() = 0;
    virtual void move(float dt);
    virtual void update(float dt);
    virtual void updateAnimation();
    virtual void onCollision(Person* other) = 0;

    // setter
    void setSpeed(float speed) { this->speed = speed; };
    void setPosition(const cocos2d::Vec2& pos) override;
    float getX() { return this->x; };
    float getY() { return this->y; };
    float getW() { return this->width; };
    float getH() { return this->height; };

protected:
    float x = 0, y = 0;
    float width = 0, height = 0;
    float speed = 0;
    bool direction_left = false;
    bool direction_right = false;
    bool direction_up = false;
    bool direction_down = false;
    cocos2d::Animation* animUp;
    cocos2d::Animation* animDown;
    cocos2d::Animation* animLeft;
    cocos2d::Animation* animRight;

    cocos2d::Animate* animateAction = nullptr;
};

#endif // PERSON_H
