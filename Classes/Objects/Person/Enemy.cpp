#include "Enemy.h"
#include "../../Scenes/GameScene.h"
#include "../../Managers/CollisionManager.h"

Enemy::Enemy(const std::string& spritePath) : Person(spritePath) {
	initAnimations();
}

void Enemy::initAnimations() {
	// Load các frame animation
	int enemyType = 1 + rand() % 4;
	std::string basePath = "images/Enemy/ene" + std::to_string(enemyType) + "/";
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

void Enemy::setAnimation(cocos2d::Vec2 direction) {
	if (fabs(direction.x) > fabs(direction.y)) {
		if (direction.x > 0) {
			this->direction_right = true;
			this->direction_left = false;
			this->direction_up = false;
			this->direction_down = false;
		}
		else {
			this->direction_right = false;
			this->direction_left = true;
			this->direction_up = false;
			this->direction_down = false;
		}
	}
	else {
		if (direction.y > 0) {
			this->direction_right = false;
			this->direction_left = false;
			this->direction_up = true;
			this->direction_down = false;
		}
		else {
			this->direction_right = false;
			this->direction_left = false;
			this->direction_up = false;
			this->direction_down = true;
		}
	}
}

void Enemy::move(float dt) {
	if (!GameScene::getPlayer()) return;

	Player* player = GameScene::getPlayer();

	cocos2d::Vec2 enemyPos = this->getPosition();
	cocos2d::Vec2 playerPos = player->getPosition();
	cocos2d::Vec2 direction = (playerPos - enemyPos).getNormalized();

	this->setPosition(enemyPos + direction * this->speed * dt);
	this->setAnimation(direction);
	if (CollisionManager::checkCollisionWithRects(this)) {
		this->setPosition(enemyPos);
	}
}

void Enemy::update(float dt) {
	if (GameManager::getInstance()->getOver()) { return; }
	this->move(dt);
	this->updateAnimation();
}