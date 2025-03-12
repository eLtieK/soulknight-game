#ifndef PERSON_H
#define PERSON_H

#include "cocos2d.h"
#include "./Utils/loader.h"

class Person : public cocos2d::Sprite {
public:
    Person(const std::string& spritePath = "", float x = WINDOW_WIDTH / 2, float y = WINDOW_HEIGHT / 2, float width = 50, float height = 50, float speed = 1000);
    /*virtual ~Person() = 0;*/

    void move(float dt);
    virtual void update(float dt);
    virtual void onCollision(Person* other) = 0;

    // setter
    void setSpeed(float speed) { this->speed = speed; };

protected:
    float x = 0, y = 0;
    float width = 0, height = 0;
    float speed = 0;
    bool direction_left = false;
    bool direction_right = false;
    bool direction_up = false;
    bool direction_down = false;
};

#endif // PERSON_H
