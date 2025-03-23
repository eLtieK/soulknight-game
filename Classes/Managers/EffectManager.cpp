#include "EffectManager.h"

void EffectManager::playEffect(cocos2d::Node* parent, const cocos2d::Vec2& position, const std::string &path, int frameCount, float delay) {
	auto animation = createAnimation(path, frameCount, delay);

	auto sprite = cocos2d::Sprite::create();
	sprite->setPosition(position);
	parent->addChild(sprite, 1);

    auto animate = cocos2d::Animate::create(animation);
    auto sequence = cocos2d::Sequence::create(
        animate,
        cocos2d::CallFunc::create([sprite]() { sprite->removeFromParentAndCleanup(true); }),
        nullptr
    );

    sprite->runAction(sequence);
}

void EffectManager::playBleedEffect(cocos2d::Node* parent, const cocos2d::Vec2& position) {
    int effectType = cocos2d::random(1, 2);
    std::string prefix = "images/effects/bleeding/bleeding" + std::to_string(effectType) + "/";
    int frameCount = (effectType == 1) ? 7 : 8;

    playEffect(parent, position, prefix, frameCount, 0.02f);
}