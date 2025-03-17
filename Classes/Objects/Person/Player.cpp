#include "Player.h"
#include "../../Factories/WeaponFactory.h"

Player::Player(const std::string& spritePath) : Person(spritePath) {
    this->weapon = WeaponFactory::createWeapon("gun");
    this->addChild(weapon);

    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    auto mouseListener = cocos2d::EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Player::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Player::onCollision(Person* other) {

}

void Player::update(float dt) {
    this->move(dt);
    this->weapon->update(dt);
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

void Player::onMouseDown(cocos2d::Event* event) {
    cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT) {
        this->weapon->attack();
    }
}
