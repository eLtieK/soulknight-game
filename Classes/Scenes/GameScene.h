#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "./Utils/Loader.h"
#include "./Factories/PlayerFactory.h"
#include "./Factories/EnemyFactory.h"
#include "./Factories/ItemFactory.h"
#include "../Objects/Weapon/Bullet.h"

class Enemy;

class GameScene : public cocos2d::Scene
{
public:
    ~GameScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    void initMap();
    void initPlayer();
    void initEnemy();
    void initCam();
    void initItem();
    void initCollisions();

    void update(float dt);
    void updateCollisions();
    
    CREATE_FUNC(GameScene);

    void addBullets(Bullet *bullet) { this->bullets.push_back(bullet); }
    void removeBullet(Bullet* bullet);

    static Player* getPlayer() { return GameScene::player; };
    std::vector<Bullet*> getBullets() { return bullets; }
    static std::vector<cocos2d::Rect> getCollisions() { return collisionRects; }

private:
    std::vector<Bullet*> bullets;
    static Player* player;
    std::vector<Enemy*> enemies;
    std::vector<Item*> items;
    cocos2d::TMXTiledMap* tileMap;
    static std::vector<cocos2d::Rect> collisionRects;
};

#endif // __GAME_SCENE_H__
