#include "GameScene.h"
#include "../Managers/CollisionManager.h"

USING_NS_CC;

const char* MAP_PATH = "data/maps/world1.tmx";
const char* MAP_PATH_1 = "newmap.tmx";

Player* GameScene::player = nullptr;
std::vector<cocos2d::Rect> GameScene::collisionRects;

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

    this->initMap();

    this->initPlayer();

    this->initEnemy();

    this->initCollisions();

    this->initItem();

    this->initCam();

    this->scheduleUpdate();
    return true;
}

void GameScene::update(float dt) {
    this->player->update(dt);

    for (Enemy* enemy : this->enemies) {
        if (enemy) enemy->update(dt);
    }

    //Collision
    CollisionManager::checkCollisionWithWeapon(player->getCurrentWeapon(), bullets, reinterpret_cast<std::vector<cocos2d::Sprite*>&>(enemies));
    CollisionManager::checkCollisionWithWeapon(player->getCurrentWeapon(), bullets, reinterpret_cast<std::vector<cocos2d::Sprite*>&>(items));
    bool isColliding = CollisionManager::checkCollisionWithPlayer(player, reinterpret_cast<std::vector<cocos2d::Sprite*>&>(enemies));
    CCLOG("Player Collision: %s", isColliding ? "YES" : "NO");
}

void GameScene::initCam() {
    auto follow = Follow::create(player, Rect(0, 0, tileMap->getContentSize().width, tileMap->getContentSize().height));
    this->runAction(follow);
}

void GameScene::initMap() {
    this->tileMap = cocos2d::TMXTiledMap::create(MAP_PATH);
    auto tileLayer = tileMap->getLayer("Main Ground");

    if (!tileMap) {
        CCLOG("Failed to load TMX map!");
        return;
    }

    this->addChild(tileMap);
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
            this->addChild(this->player);
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

        this->addChild(enemy);
        this->enemies.push_back(enemy);
    }
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

        this->addChild(item);
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
