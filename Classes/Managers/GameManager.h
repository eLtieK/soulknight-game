#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"

class GameManager {
public:
    static GameManager* getInstance();
    void setOver(bool isOver) { this->isOver = isOver; CCLOG("Game Over state set to: %s", isOver ? "true" : "false");}
    bool getOver() const { return this->isOver; }

    void setBoss(bool isBoss) { this->isBoss = isBoss; CCLOG("Boss state set to: %s", isBoss ? "true" : "false");}
    bool getBoss() const { return this->isBoss; }

    void setEnemy(bool isEnemy) { this->isEnemy = isEnemy; CCLOG("Enemy state set to: %s", isEnemy ? "true" : "false");}
    bool getEnemy() const { return this->isEnemy; }

private:
    static GameManager* instance;
    bool isOver = false;
    bool isBoss = false;
    bool isEnemy = false;
};

#endif // __GAME_MANAGER_H__
