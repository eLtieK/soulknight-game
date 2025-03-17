#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"
#include "../Weapon/Weapon.h"

class Player : public Person {
public:
    Player(const std::string& spritePath = "");
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onMouseDown(cocos2d::Event* event);
    void update(float dt) override;
    void onCollision(Person* other) override;
    void attack();

private:
    Weapon* weapon;
};

#endif // PLAYER_H
