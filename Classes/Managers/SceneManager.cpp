#include "SceneManager.h"
#include "Scenes/GameScene.h"
#include "Scenes/MainMenuScene.h"

USING_NS_CC;

void SceneManager::goToGameScene() {
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void SceneManager::goToMainMenu() {
    /*auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(scene);*/
}
