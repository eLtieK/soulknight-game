#ifndef __ABOUT_LAYER_H__
#define __ABOUT_LAYER_H__

#include "cocos2d.h"

class AboutLayer : public cocos2d::LayerColor
{
public:
    static AboutLayer* create();
    void onClose(cocos2d::Ref* sender);
};

#endif // __ABOUT_LAYER_H__
