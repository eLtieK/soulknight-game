#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->player = PlayerFactory::createPlayer("");
    this->addChild(player);

    this->scheduleUpdate();
    return true;
}

void GameScene::update(float dt) {
    this->player->update(dt);
}