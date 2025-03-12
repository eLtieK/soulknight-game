#include "GameManager.h"

USING_NS_CC;

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance() {
    if (instance == nullptr) {
        instance = new GameManager();
    }
    return instance;
}   