#ifndef WEAPON_H
#define WEAPON_H

#include "cocos2d.h"
#include "../../Utils/loader.h"

class Weapon : public cocos2d::Sprite {
public:
    Weapon(const std::string& spritePath = "", float width = 50, float height = 50);
    virtual void attack() = 0;
    void followMouse(bool isRotate, bool isFlip);
    void update(float dt) override;

protected:
    float offset = 100.0f;
    cocos2d::Vec2 lastMousePos;
};

#endif // WEAPON_H
