#include "AboutLayer.h"

USING_NS_CC;

AboutLayer* AboutLayer::create()
{
    AboutLayer* ret = new (std::nothrow) AboutLayer();
    if (ret && ret->initWithColor(Color4B(0, 0, 0, 180)))
    {
        ret->autorelease();

        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        // Hiển thị hướng dẫn chơi
        auto aboutLabel = Label::createWithTTF("How to Play:\n\n- W, A, S, D: Move\n- Left Mouse: Attack\n- Q: Switch Weapon", "fonts/Marker Felt.ttf", 32);
        aboutLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
        ret->addChild(aboutLabel);

        // Nút đóng About
        auto closeLabel = Label::createWithTTF("CLOSE", "fonts/Marker Felt.ttf", 28);
        auto closeButton = MenuItemLabel::create(closeLabel, CC_CALLBACK_1(AboutLayer::onClose, ret));
        closeButton->setPosition(origin.x + visibleSize.width / 2, origin.y + 50);

        auto menu = Menu::create(closeButton, nullptr);
        menu->setPosition(Vec2::ZERO);
        ret->addChild(menu);

        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void AboutLayer::onClose(cocos2d::Ref* sender)
{
    this->removeFromParentAndCleanup(true);
}
