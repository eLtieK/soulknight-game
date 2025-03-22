#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"
#include "../Weapon/Weapon.h"
#include <vector>

class Player : public Person {
public:
    Player(const std::string& spritePath = "");
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onMouseDown(cocos2d::Event* event);
    void update(float dt) override;
    void onCollision(Person* other) override;
    void initAnimations() override;
    void switchWeapon();

    Weapon* getCurrentWeapon() { return this->currentWeapon; };

private:
    std::vector<Weapon*> weapons;
    Weapon* currentWeapon;
    int weaponIndex;
};

#endif // PLAYER_H
