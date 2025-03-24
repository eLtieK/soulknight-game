#include "GameScene.h"
#include "../Managers/CollisionManager.h"
#include "../Managers/SoundManager.h"

USING_NS_CC;

const char* MAP_PATH = "data/maps/world1.tmx";

Player* GameScene::player = nullptr;
std::vector<cocos2d::Rect> GameScene::collisionRects;

GameScene::~GameScene() {
    // Xóa danh sách enemy
    for (Enemy* enemy : this->enemies) {
        if (enemy) {
            enemy->removeFromParentAndCleanup(true);
            delete enemy;
        }
    }
    this->enemies.clear();

    // Xóa danh sách bullet
    for (Bullet* bullet : this->bullets) {
        if (bullet) {
            bullet->removeFromParentAndCleanup(true);
            delete bullet;
        }
    }
    this->bullets.clear();

    // Xóa danh sách item
    for (Item* item : this->items) {
        if (item) {
            item->removeFromParentAndCleanup(true);
            delete item;
        }
    }
    this->items.clear();

    // Giải phóng Player (nếu tồn tại)
    /*if (GameScene::player) {
        GameScene::player->removeFromParentAndCleanup(true);
        delete GameScene::player;
        GameScene::player = nullptr;
    }*/

    // Xóa bản đồ (tileMap)
    if (tileMap) {
        tileMap->removeFromParentAndCleanup(true);
        tileMap = nullptr;
    }

    // Xóa danh sách collisionRects
    /*GameScene::collisionRects.clear();*/
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

    GameManager::getInstance()->setBoss(false);
    GameManager::getInstance()->setEnemy(false);
    GameManager::getInstance()->setOver(false);
    GameManager::getInstance()->setCoins(0);
    GameManager::getInstance()->setEnemyLeft(0);

    this->initMap();

    this->initPlayer();

    this->initEnemy();

    this->initCollisions();

    this->initItem();

    this->initCam();

    this->initUi();

    this->scheduleUpdate();
    return true;
}

void GameScene::update(float dt) {
    if (GameManager::getInstance()->getOver()) { return; }

    this->player->update(dt);

    for (Enemy* enemy : this->enemies) {
        if (enemy) enemy->update(dt);
    }
    
    cocos2d::Vec2 newUIpos = player->getPosition() - Director::getInstance()->getVisibleSize() / 2;
    this->ui->updateUI(newUIpos, GameManager::getInstance()->getCoins(), GameManager::getInstance()->getEnemyLeft());

    //Collision
    CollisionManager::checkCollisionWithWeapon(player->getCurrentWeapon(), bullets, reinterpret_cast<std::vector<cocos2d::Sprite*>&>(enemies));
    CollisionManager::checkCollisionWithWeapon(player->getCurrentWeapon(), bullets, reinterpret_cast<std::vector<cocos2d::Sprite*>&>(items));
    CollisionManager::checkCollisionWithPlayer(player, reinterpret_cast<std::vector<cocos2d::Sprite*>&>(items));

    bool isOver = CollisionManager::checkCollisionWithPlayer(player, reinterpret_cast<std::vector<cocos2d::Sprite*>&>(enemies));
    if (isOver && !GameManager::getInstance()->getOver()) {
        SoundManager::playFail();
        GameManager::getInstance()->setOver(isOver);
        GameOverLayer* fakeLayer = GameOverLayer::createFake("Game Over");
        cocos2d::Director::getInstance()->getRunningScene()->addChild(fakeLayer, 10);
        cocos2d::Director::getInstance()->getRunningScene()->addChild(GameOverLayer::create(fakeLayer), 0);
    }

    //Boss
    if ((this->enemies.size() <= 5 && this->enemies.size() > 0) && !GameManager::getInstance()->getBoss() && GameManager::getInstance()->getEnemy()) {
        SoundManager::playBoss();
        GameManager::getInstance()->setBoss(true);
        GameManager::getInstance()->setEnemy(false);
        this->initBoss();
    }
    if (this->enemies.empty() && GameManager::getInstance()->getBoss()) {
        SoundManager::playWin();
        GameManager::getInstance()->setOver(true);
        GameManager::getInstance()->setBoss(false);
        GameOverLayer* fakeLayer = GameOverLayer::createFake("Victory");
        cocos2d::Director::getInstance()->getRunningScene()->addChild(fakeLayer, 10);
        cocos2d::Director::getInstance()->getRunningScene()->addChild(GameOverLayer::create(fakeLayer), 0);  
    }
}

void GameScene::initCam() {
    //auto follow = Follow::create(player);
    auto follow = Follow::create(player, Rect(0, 0, tileMap->getContentSize().width, tileMap->getContentSize().height));
    this->runAction(follow);
}

void GameScene::initUi() {
    this->ui = UILayer::create();
    this->addChild(ui, 2);
}

void GameScene::initMap() {
    this->tileMap = cocos2d::TMXTiledMap::create(MAP_PATH);
    auto tileLayer = tileMap->getLayer("Main Ground");

    if (!tileMap) {
        CCLOG("Failed to load TMX map!");
        return;
    }

    this->addChild(tileMap, 1);
}

void GameScene::removeBullet(Bullet* bullet) {
    auto it = std::find(bullets.begin(), bullets.end(), bullet);
    if (it != bullets.end()) {
        bullets.erase(it);
        bullet->removeFromParentAndCleanup(true);
    }
}

void GameScene::updateCollisions() {
    Vec2 tileMapPos = tileMap->getPosition(); // Lấy vị trí mới của tilemap

    for (auto& rect : collisionRects) {
        float x = rect.origin.x - tileMap->getPosition().x;
        float y = rect.origin.y - tileMap->getPosition().y;
        float width = rect.size.width, height = rect.size.height;
        auto debugRect = cocos2d::DrawNode::create();
        debugRect->drawRect(cocos2d::Vec2(x, y), cocos2d::Vec2(x + width, y + height), cocos2d::Color4F::WHITE);
        tileMap->addChild(debugRect);
    }
}


void GameScene::initPlayer() {
    auto objectGroup = tileMap->getObjectGroup("Entities");
    auto objects = objectGroup->getObjects();
    for (const auto& obj : objects) {
        auto objMap = obj.asValueMap();

        // Kiểm tra nếu object có tên "Player"
        if (objMap["name"].asString() == "Player") {
            float x = objMap["x"].asFloat();
            float y = objMap["y"].asFloat();

            // Tạo player tại vị trí này
            this->player = PlayerFactory::createPlayer("");
            this->player->setPosition(cocos2d::Vec2(WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 + 100));

            this->addChild(this->player, 1);
            return;
        }
    }

}

void GameScene::initEnemy() {
    auto objectGroup = tileMap->getObjectGroup("Entities");
    auto objects = objectGroup->getObjects();
    for (const auto& obj : objects) {
        auto objMap = obj.asValueMap();

        std::string objName = objMap["name"].asString();
        if (objName != "Enemy") continue;

        float x = objMap["x"].asFloat();
        float y = objMap["y"].asFloat();

        Enemy* enemy = EnemyFactory::createEnemy("");
        enemy->setPosition(Vec2(x, y));

        float speed = (float)(100 + rand() % 151); //random tu 100-150

        enemy->setSpeed(speed);

        this->addChild(enemy, 1);
        this->enemies.push_back(enemy);
    }
    if (!this->enemies.empty()) { GameManager::getInstance()->setEnemy(true); }
    GameManager::getInstance()->setEnemyLeft(this->enemies.size());
}

void GameScene::initBoss() {
    auto objectGroup = tileMap->getObjectGroup("Entities");
    auto objects = objectGroup->getObjects();
    for (const auto& obj : objects) {
        auto objMap = obj.asValueMap();

        std::string objName = objMap["name"].asString();
        if (objName != "Boss") continue;

        float x = objMap["x"].asFloat();
        float y = objMap["y"].asFloat();

        Enemy* enemy = EnemyFactory::createEnemy("boss");
        enemy->setPosition(Vec2(x, y));

        this->addChild(enemy, 1);
        this->enemies.push_back(enemy);
        break;
    }
    GameManager::getInstance()->setEnemyLeft(1);
}

void GameScene::initItem() {
    auto objectGroup = tileMap->getObjectGroup("Objects");
    auto objects = objectGroup->getObjects();
    for (const auto& obj : objects) {
        auto objMap = obj.asValueMap();

        std::string objName = objMap["name"].asString();
        if (objName != "Jar") continue;

        float x = objMap["x"].asFloat();
        float y = objMap["y"].asFloat();

        Item* item = ItemFactory::createItem("jar");
        item->setPosition(Vec2(x, y));

        this->addChild(item, 1);
        this->items.push_back(item);
    }
}

void GameScene::initCollisions() {
    auto objectGroup = tileMap->getObjectGroup("Collisions");
    auto objects = objectGroup->getObjects();
    for (const auto& obj : objects) {
        auto objMap = obj.asValueMap();

        float x = objMap["x"].asFloat();
        float y = objMap["y"].asFloat();
        float width = objMap["width"].asFloat();
        float height = objMap["height"].asFloat();


        cocos2d::Rect rect(x, y, width, height);
        collisionRects.push_back(rect);
    }
}
