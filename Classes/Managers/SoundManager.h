#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "cocos2d.h"

class SoundManager {
public:
    static void playEffect(const std::string& sound, bool loop = false);
    static void playShoot();
    static void playBleed();
    static void playMove();
    static void playSword();
    static void playGold();
    static void playJar();
    static void playButton();
    static void playTheme();

    static void stopMove();

private:
    static int moveSoundId;
    static int themeSoundId;
};

#endif // SOUND_MANAGER_H
