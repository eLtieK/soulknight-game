#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "./Utils/Loader.h"
#include "./Factories/PlayerFactory.h"
#include "./Factories/EnemyFactory.h"

class Enemy;

class GameScene : public cocos2d::Scene
{
public:
    ~GameScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(float dt);
    CREATE_FUNC(GameScene);

    static Player* getPlayer() { return GameScene::player; };

private:
    static Player* player;
    std::vector<Enemy*> enemies;
};

#endif // __GAME_SCENE_H__
