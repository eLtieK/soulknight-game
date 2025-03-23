#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__

#include "cocos2d.h"

class GameOverLayer : public cocos2d::LayerColor {
public:
    static GameOverLayer* create(GameOverLayer* other);
    static GameOverLayer* createFake();

    void onNewGame(cocos2d::Ref* sender, GameOverLayer* other);
    void onMainMenu(cocos2d::Ref* sender, GameOverLayer* other);
    void onQuit(cocos2d::Ref* sender);

private:
    static GameOverLayer* instance;
};

#endif // __GAMEOVER_LAYER_H__
