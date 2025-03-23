#ifndef __UI_LAYER_H__
#define __UI_LAYER_H__

#include "cocos2d.h"

class UILayer : public cocos2d::Layer {
public:
    static UILayer* createLayer();
    virtual bool init();
    void updateUI(cocos2d::Vec2 pos, int coins, int enemiesLeft); // Hàm cập nhật UI
    CREATE_FUNC(UILayer);

private:
    cocos2d::Label* coinLabel;
    cocos2d::Label* enemyLabel;
};

#endif // __UI_LAYER_H__
