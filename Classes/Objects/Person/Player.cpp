#include "Player.h"
#include "../../Factories/WeaponFactory.h"
#include "../../Scenes/GameScene.h"
#include "../../Managers/SoundManager.h"

void Player::initAnimations() {
    // Load các frame animation
    animUp = createAnimation("images/Player/up/", 3, 0.1f);
    animDown = createAnimation("images/Player/down/", 3, 0.1f);
    animLeft = createAnimation("images/Player/left/", 3, 0.1f);
    animRight = createAnimation("images/Player/right/", 3, 0.1f);
    standing = createAnimation("images/Player/standing/", 5, 0.1f);

    animUp->setLoops(-1);
    animDown->setLoops(-1);
    animLeft->setLoops(-1);
    animRight->setLoops(-1);
    standing->setLoops(-1);

    animUp->retain();
    animDown->retain();
    animLeft->retain();
    animRight->retain();
    standing->retain();
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

Player::~Player() {
    // Xóa tất cả vũ khí trong danh sách weapons
    for (Weapon* weapon : weapons) {
        if (weapon) {
            weapon->removeFromParentAndCleanup(true);
            delete weapon;
        }
    }
    weapons.clear();

    // Xóa vũ khí hiện tại nếu chưa có trong weapons (tránh xóa 2 lần)
    if (currentWeapon) {
        currentWeapon = nullptr;
    }
}

void Player::update(float dt) {
    this->move(dt);
    this->currentWeapon->update(dt);
    this->updateAnimation();
    if (direction_left || direction_down || direction_right || direction_up) SoundManager::playMove();
    else SoundManager::stopMove();
}

void Player::updateAnimation() {
    if (!this->direction_down && !this->direction_left && !this->direction_right && !this->direction_up) {
        if (animateAction == nullptr) {
            animateAction = cocos2d::Animate::create(standing);
            this->runAction(animateAction);
            CCLOG("INIT STAND");
        }
        else if (animateAction->getAnimation() != standing) {
            this->stopAllActions();
            animateAction = cocos2d::Animate::create(standing);
            this->runAction(animateAction);
            CCLOG("REINIT STAND");
        }
    }
    Person::updateAnimation();
}

void Player::switchWeapon() {
    SoundManager::playEquip();
    this->currentWeapon->removeFromParentAndCleanup(true);

    this->weaponIndex = (weaponIndex + 1) % weapons.size();
    this->currentWeapon = weapons[weaponIndex];

    this->addChild(currentWeapon);
}

void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (GameManager::getInstance()->getOver()) { return; }
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A) this->direction_left = true;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) this->direction_right = true;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S) this->direction_down = true;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W) this->direction_up = true;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Q) this->switchWeapon();
}

void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (GameManager::getInstance()->getOver()) { return; }
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A) this->direction_left = false;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) this->direction_right = false;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S) this->direction_down = false;
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W) this->direction_up = false;
}

void Player::onMouseDown(cocos2d::Event* event) {
    if (GameManager::getInstance()->getOver()) { return; }
    cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT) {
        this->currentWeapon->attack();
        SoundManager::playShoot();
    }
}
