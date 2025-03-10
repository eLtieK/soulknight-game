#include "SoundManager.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;

SoundManager* SoundManager::getInstance() {
    static SoundManager instance;
    return &instance;
}

void SoundManager::playEffect(const std::string& sound) {
    AudioEngine::play2d(sound);
}
