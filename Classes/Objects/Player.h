#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"

class Player : public Person {
public:
    Player(const std::string& spritePath = "");
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void update(float dt) override;
    void onCollision(Person* other) override;
};

#endif // PLAYER_H
