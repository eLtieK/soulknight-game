#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"

class GameManager {
public:
    static GameManager* getInstance();
    void setOver(bool isOver) { this->isOver = isOver; }
    bool getOver() { return this->isOver; }

private:
    static GameManager* instance;
    bool isOver = false;
};

#endif // __GAME_MANAGER_H__
