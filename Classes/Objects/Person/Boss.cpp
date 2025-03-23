#include "Boss.h"

Boss::Boss(const std::string& spritePath, int maxHits)
    : Enemy(spritePath), maxHit(maxHits), hitTaken(0) {
    this->setScale(2.0f);
    this->setSpeed(400);

	initAnimations();
}

void Boss::initAnimations() {
	std::string basePath = "images/Enemy/boss/";
	animUp = createAnimation(basePath + "up/", 3, 0.1f);
	animDown = createAnimation(basePath + "down/", 3, 0.1f);
	animLeft = createAnimation(basePath + "left/", 3, 0.1f);
	animRight = createAnimation(basePath + "right/", 3, 0.1f);

	animUp->setLoops(-1);
	animDown->setLoops(-1);
	animLeft->setLoops(-1);
	animRight->setLoops(-1);

	animUp->retain();
	animDown->retain();
	animLeft->retain();
	animRight->retain();
}