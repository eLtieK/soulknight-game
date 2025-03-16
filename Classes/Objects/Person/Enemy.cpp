#include "Enemy.h"
#include "../../Scenes/GameScene.h"

Enemy::Enemy(const std::string& spritePath) : Person(spritePath) {
	
}

void Enemy::move(float dt) {
	if (!GameScene::getPlayer()) return;

	Player* player = GameScene::getPlayer();

	cocos2d::Vec2 enemyPos = this->getPosition();
	cocos2d::Vec2 playerPos = player->getPosition();
	cocos2d::Vec2 direction = (playerPos - enemyPos).getNormalized();

	this->setPosition(enemyPos + direction * this->speed * dt);
}

void Enemy::update(float dt) {
	this->move(dt);
}

void Enemy::onCollision(Person * other) {

}