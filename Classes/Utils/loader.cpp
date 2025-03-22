#include "loader.h"

cocos2d::Animation* createAnimation(const std::string& prefixName, int frameCount, float delay) {
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;
    for (int i = 1; i <= frameCount; i++) {
        std::string frameName = prefixName + std::to_string(i) + ".png";
        auto texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(frameName);
        if (!texture) {
            CCLOG("Image not found: %s", frameName.c_str());
            continue;
        }

        auto frame = cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
        if (frame) {
            frames.pushBack(frame);
        }
    }
    return cocos2d::Animation::createWithSpriteFrames(frames, delay);
}