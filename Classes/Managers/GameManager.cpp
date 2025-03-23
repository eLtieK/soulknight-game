#include "GameManager.h"

USING_NS_CC;

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance() {
    if (GameManager::instance == nullptr) {
        GameManager::instance = new GameManager();
    }
    return GameManager::instance;
}   