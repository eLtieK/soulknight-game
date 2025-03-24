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

void MainMenuScene::initBackground() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("images/theme.jpg"); // Thay "background.png" bằng tên file ảnh của bạn
    background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

    // Điều chỉnh kích thước cho phù hợp với màn hình
    background->setContentSize(visibleSize);

    this->addChild(background, 0); // Thêm background vào scene với z-order thấp nhất

}

bool MainMenuScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->initBackground();

    // Thêm tiêu đề "Pixel Crusader"
    auto titleLabel = Label::createWithTTF("Pixel Crusader", "fonts/Marker Felt.ttf", 102);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.height - 200));
    titleLabel->setColor(Color3B::WHITE);
    this->addChild(titleLabel, 1);

    // Tạo Label cho nút Start
    auto playLabel = Label::createWithTTF("START GAME", "fonts/Marker Felt.ttf", 64);
    auto playItem = MenuItemLabel::create(playLabel, [](Ref* sender) {
        SoundManager::playButton();
        auto gameScene = GameScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.f, gameScene));
        });

    // Nút About
    auto aboutLabel = Label::createWithTTF("ABOUT", "fonts/Marker Felt.ttf", 64);
    auto aboutItem = MenuItemLabel::create(aboutLabel, CC_CALLBACK_1(MainMenuScene::onAbout, this));

    auto quitLabel = Label::createWithTTF("QUIT GAME", "fonts/Marker Felt.ttf", 64);
    auto quitItem = MenuItemLabel::create(quitLabel, [](Ref* sender) {
        SoundManager::playButton();
        Director::getInstance()->end();
        });

    auto menu = Menu::create(playItem, aboutItem, quitItem, nullptr);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setPosition(visibleSize.width / 4, visibleSize.height* 2/ 5);
    this->addChild(menu);

    SoundManager::playTheme();

    return true;
}
