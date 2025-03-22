#include "Player.h"
#include "../../Factories/WeaponFactory.h"
#include "../../Scenes/GameScene.h"

void Player::initAnimations() {
    // Load các frame animation
    animUp = createAnimation("images/Player/up/", 3, 0.1f);
    animDown = createAnimation("images/Player/down/", 3, 0.1f);
    animLeft = createAnimation("images/Player/left/", 3, 0.1f);
    animRight = createAnimation("images/Player/right/", 3, 0.1f);

    animUp->setLoops(-1);
    animDown->setLoops(-1);
    animLeft->setLoops(-1);
    animRight->setLoops(-1);

    animUp->retain();
    animDown->retain();
    animLeft->retain();
    animRight->retain();
}

Player::Player(const std::string& spritePath) : Person(spritePath) {
    this->weapons.push_back(WeaponFactory::createWeapon("gun"));
    this->weapons.push_back(WeaponFactory::createWeapon("sword"));
    this->currentWeapon = weapons[0];
    this->addChild(currentWeapon);

    initAnimations();

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
    this->currentWeapon->update(dt);
    this->updateAnimation();
}

void Player::switchWeapon() {
    this->currentWeapon->removeFromParentAndCleanup(true);

    this->weaponIndex = (weaponIndex + 1) % weapons.size();
    this->currentWeapon = weapons[weaponIndex];

    this->addChild(currentWeapon);
}

void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A) this->direction_left = true;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) this->direction_right = true;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S) this->direction_down = true;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W) this->direction_up = true;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Q) this->switchWeapon();
}

void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A) this->direction_left = false;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) this->direction_right = false;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S) this->direction_down = false;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W) this->direction_up = false;
}

void Player::onMouseDown(cocos2d::Event* event) {
    cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT) {
        this->currentWeapon->attack();
    }
}
