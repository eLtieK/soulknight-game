#ifndef PERSON_H
#define PERSON_H

#include "cocos2d.h"

class Person : public cocos2d::Sprite {
public:
    virtual void move(float dx, float dy);
    virtual void update(float dt);
    virtual void onCollision(Person* other) = 0;
};

#endif // PERSON_H
