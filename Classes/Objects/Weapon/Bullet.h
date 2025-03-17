#ifndef BULLET_H
#define BULLET_H

#include "cocos2d.h"
#include "../../Utils/loader.h"

class Bullet : public cocos2d::Sprite {
private:
    float speed;
    cocos2d::Vec2 direction;

public:
    Bullet(const std::string& spritePath = "", float width = 50, float height = 50, cocos2d::Vec2 direction = (0,0), float speed = 500);
    void update(float dt) override;
};

#endif // BULLET_H
