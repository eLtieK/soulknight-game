#ifndef __EFFECT_MANAGER_H__
#define __EFFECT_MANAGER_H__

#include "cocos2d.h"
#include "../Utils/loader.h"

class EffectManager {
public:
    static void playBleedEffect(cocos2d::Node* parent, const cocos2d::Vec2& position);
    static void playEffect(cocos2d::Node* parent, const cocos2d::Vec2& position, const std::string& path, int frameCount, float delay);

private:
};

#endif // __EFFECT_MANAGER_H__
