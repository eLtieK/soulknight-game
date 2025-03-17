#include "GameScene.h"

USING_NS_CC;

Player* GameScene::player = nullptr;

GameScene::~GameScene() {
    for (Enemy* enemy : this->enemies) {
        delete enemy;
    }
    this->enemies.clear();

    if (GameScene::player) delete GameScene::player;
}

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

    for (int i = 0; i < 10; i++) {
        Enemy* enemy = EnemyFactory::createEnemy("");
        float x = (float) (rand() % WINDOW_WIDTH);
        float y = (float) (rand() % WINDOW_HEIGHT);
        float speed = (float) (50 + rand() % 151); //random tu 100-150

        enemy->setPosition(Vec2(x, y));
        enemy->setSpeed(speed);

        this->addChild(enemy);
        this->enemies.push_back(enemy); // Save to list
    }

    this->scheduleUpdate();
    return true;
}

void GameScene::update(float dt) {
    this->player->update(dt);

    for (Enemy* enemy : this->enemies) {
        if (enemy) enemy->update(dt);
    }
}