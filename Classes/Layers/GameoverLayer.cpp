#include "GameoverLayer.h"
#include "../Scenes/GameScene.h"
#include "../Scenes/MainMenuScene.h"
#include "../Managers/GameManager.h"
#include "ui/CocosGUI.h"
#include "../Managers/SoundManager.h"

GameOverLayer* GameOverLayer::instance = nullptr;

GameOverLayer* GameOverLayer::createFake(const std::string& title) {
    GameOverLayer* ret = new (std::nothrow) GameOverLayer();
    ret->setPosition(GameScene::getPlayer()->getPosition() - cocos2d::Director::getInstance()->getVisibleSize() / 2);
    if (ret && ret->initWithColor(cocos2d::Color4B(0, 0, 0, 180))) {
        ret->autorelease();

        cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

        // Tiêu đề "Game Over"
        auto gameOverLabel = cocos2d::Label::createWithTTF(title, "fonts/Marker Felt.ttf", 62);
        gameOverLabel->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height - 100));
        ret->addChild(gameOverLabel);

        // Nút New Game
        auto newGameLabel = cocos2d::Label::createWithTTF("New Game", "fonts/Marker Felt.ttf", 48);
        auto newGameButton = cocos2d::MenuItemLabel::create(newGameLabel);

        // Nút Main Menu
        auto mainMenuLabel = cocos2d::Label::createWithTTF("Main Menu", "fonts/Marker Felt.ttf", 48);
        auto mainMenuButton = cocos2d::MenuItemLabel::create(mainMenuLabel);

        // Nút Quit
        auto quitLabel = cocos2d::Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 48);
        auto quitButton = cocos2d::MenuItemLabel::create(quitLabel);

        // Menu chứa các nút
        auto menu = cocos2d::Menu::create(newGameButton, mainMenuButton, quitButton, nullptr);
        menu->alignItemsVerticallyWithPadding(20);
        //menu->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
        ret->addChild(menu);

        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GameOverLayer* GameOverLayer::create(GameOverLayer* other) {
    GameOverLayer* ret = new (std::nothrow) GameOverLayer();
    /*ret->setPosition(GameScene::getPlayer()->getPosition() - cocos2d::Director::getInstance()->getVisibleSize() / 2);*/
    if (ret && ret->initWithColor(cocos2d::Color4B(0, 0, 0, 180))) {
        ret->autorelease();

        cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

        // Tiêu đề "Game Over"
        auto gameOverLabel = cocos2d::Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 62);
        gameOverLabel->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height - 100));
        ret->addChild(gameOverLabel);

        // Nút New Game
        auto newGameLabel = cocos2d::Label::createWithTTF("New Game", "fonts/Marker Felt.ttf", 48);
        auto newGameButton = cocos2d::MenuItemLabel::create(newGameLabel, CC_CALLBACK_1(GameOverLayer::onNewGame, ret, other));

        // Nút Main Menu
        auto mainMenuLabel = cocos2d::Label::createWithTTF("Main Menu", "fonts/Marker Felt.ttf", 48);
        auto mainMenuButton = cocos2d::MenuItemLabel::create(mainMenuLabel, CC_CALLBACK_1(GameOverLayer::onMainMenu, ret, other));

        // Nút Quit
        auto quitLabel = cocos2d::Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 48);
        auto quitButton = cocos2d::MenuItemLabel::create(quitLabel, CC_CALLBACK_1(GameOverLayer::onQuit, ret));

        // Menu chứa các nút
        auto menu = cocos2d::Menu::create(newGameButton, mainMenuButton, quitButton, nullptr);
        menu->alignItemsVerticallyWithPadding(20);
        //menu->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
        ret->addChild(menu);

        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

// Xử lý khi chọn New Game
void GameOverLayer::onNewGame(cocos2d::Ref* sender, GameOverLayer* other) {
    SoundManager::playButton();
    other->removeFromParentAndCleanup(true);
    this->removeFromParentAndCleanup(true);
    cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1.f, GameScene::createScene()));
}

// Xử lý khi chọn Main Menu
void GameOverLayer::onMainMenu(cocos2d::Ref* sender, GameOverLayer* other) {
    SoundManager::playButton();
    other->removeFromParentAndCleanup(true);
    this->removeFromParentAndCleanup(true);
    cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1.f, MainMenuScene::createScene()));
}

// Xử lý khi chọn Quit
void GameOverLayer::onQuit(cocos2d::Ref* sender) {
    SoundManager::playButton();
    cocos2d::Director::getInstance()->end();
}
