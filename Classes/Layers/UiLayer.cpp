#include "UILayer.h"

USING_NS_CC;

UILayer* UILayer::createLayer() {
    UILayer* layer = UILayer::create();
    return layer;
}

bool UILayer::init() {
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Tạo label hiển thị số coin
    coinLabel = Label::createWithTTF("Coins: 0", "fonts/Marker Felt.ttf", 36);
    coinLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 100);
    this->addChild(coinLabel);

    // Tạo label hiển thị số Enemy còn lại
    enemyLabel = Label::createWithTTF("Enemies Left: 0", "fonts/Marker Felt.ttf", 36);
    enemyLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50);
    this->addChild(enemyLabel);

    return true;
}

void UILayer::updateUI(cocos2d::Vec2 pos, int coins, int enemiesLeft) {
    this->setPosition(pos);
    coinLabel->setString("Coins: " + std::to_string(coins));
    enemyLabel->setString("Enemies Left: " + std::to_string(enemiesLeft));
}