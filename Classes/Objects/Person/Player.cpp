#include "Player.h"

Player::Player(const std::string& spritePath) : Person(spritePath) {
    auto eventListener = cocos2d::EventListenerKeyboard::create();

    eventListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    eventListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void Player::onCollision(Person* other) {

}

void Player::update(float dt) {
    this->move(dt);
}

void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) this->direction_left = true;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) this->direction_right = true;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW) this->direction_down = true;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) this->direction_up = true;
}

void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) this->direction_left = false;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) this->direction_right = false;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW) this->direction_down = false;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) this->direction_up = false;
}
