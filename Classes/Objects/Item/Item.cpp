#include "Item.h"

Item::Item(const std::string& spritePath, float width, float height) {
    if (!spritePath.empty())
        this->initWithFile(spritePath);
    else {
        this->init();
        this->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
        this->setTextureRect(cocos2d::Rect(0, 0, width, height));
        this->setColor(cocos2d::Color3B::WHITE);
    }
}