#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "./Utils/Loader.h"
#include "./Factories/PlayerFactory.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(float dt);
    CREATE_FUNC(GameScene);

private:
    Player* player;
};

#endif // __GAME_SCENE_H__
