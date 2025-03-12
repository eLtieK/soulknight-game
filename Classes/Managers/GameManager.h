#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"

class GameManager {
private:
    static GameManager* instance;

public:
    static GameManager* getInstance();
};

#endif // __GAME_MANAGER_H__
