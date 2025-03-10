#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "cocos2d.h"

class SoundManager {
public:
    static SoundManager* getInstance();
    void playEffect(const std::string& sound);
};

#endif // SOUND_MANAGER_H
