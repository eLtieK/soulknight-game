#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

bool MainMenuScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Tạo Label cho nút Start
    auto label = Label::createWithTTF("START GAME", "fonts/Marker Felt.ttf", 48);
    auto menuItem = MenuItemLabel::create(label, [](Ref* sender) {
        auto gameScene = GameScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.2f, gameScene));
        });

    menuItem->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    auto menu = Menu::create(menuItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}
