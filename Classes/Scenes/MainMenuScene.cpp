#include "MainMenuScene.h"
#include "GameScene.h"
#include "../Managers/SoundManager.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

void MainMenuScene::onAbout(cocos2d::Ref* sender) {
    SoundManager::playButton();
    auto aboutLayer = AboutLayer::create();
    this->addChild(aboutLayer, 1);
}

bool MainMenuScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Tạo Label cho nút Start
    auto playLabel = Label::createWithTTF("START GAME", "fonts/Marker Felt.ttf", 48);
    auto playItem = MenuItemLabel::create(playLabel, [](Ref* sender) {
        SoundManager::playButton();
        auto gameScene = GameScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.f, gameScene));
        });

    // Nút About
    auto aboutLabel = Label::createWithTTF("ABOUT", "fonts/Marker Felt.ttf", 48);
    auto aboutItem = MenuItemLabel::create(aboutLabel, CC_CALLBACK_1(MainMenuScene::onAbout, this));

    auto quitLabel = Label::createWithTTF("QUIT GAME", "fonts/Marker Felt.ttf", 48);
    auto quitItem = MenuItemLabel::create(quitLabel, [](Ref* sender) {
        SoundManager::playButton();
        Director::getInstance()->end();
        });

    auto menu = Menu::create(playItem, aboutItem, quitItem, nullptr);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(menu);

    SoundManager::playTheme();

    return true;
}
