#include "SoundManager.h"
#include "audio/include/AudioEngine.h"

int SoundManager::moveSoundId = -1;
int SoundManager::themeSoundId = -1;

void SoundManager::playEffect(const std::string& sound, bool loop) {
    cocos2d::AudioEngine::play2d(sound, loop);
}

void SoundManager::playShoot() {
    SoundManager::playEffect("sounds/shoot.mp3");
}

void SoundManager::playBleed() {
    SoundManager::playEffect("sounds/bleed.mp3");
}

void SoundManager::playMove() {
    if (moveSoundId != -1 && cocos2d::AudioEngine::getState(moveSoundId) == cocos2d::AudioEngine::AudioState::PLAYING) {
        return;  // Đang phát thì không phát lại
    }
    moveSoundId = cocos2d::AudioEngine::play2d("sounds/move.mp3");
}

void SoundManager::stopMove() {
    if (moveSoundId != -1) {
        cocos2d::AudioEngine::stop(moveSoundId);
    }
    moveSoundId = -1;
}

void SoundManager::playSword() {
    int type = cocos2d::random(1, 2);
    SoundManager::playEffect("sounds/sword" + std::to_string(type) + ".mp3");
}

void SoundManager::playGold() {
    SoundManager::playEffect("sounds/gold.mp3");
}

void SoundManager::playJar() {
    SoundManager::playEffect("sounds/jar.mp3");
}

void SoundManager::playButton() {
    SoundManager::playEffect("sounds/button.mp3");
}

void SoundManager::playTheme() {
    if (themeSoundId != -1 && cocos2d::AudioEngine::getState(themeSoundId) == cocos2d::AudioEngine::AudioState::PLAYING) {
        return;
    }
    themeSoundId = cocos2d::AudioEngine::play2d("sounds/theme.mp3", true);
}

