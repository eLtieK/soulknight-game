#include "Player.h"

Player* Player::create() {
    Player* player = new Player();
    if (player && player->initWithFile("player.png")) {
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

void Player::jump() {
    this->setPositionY(this->getPositionY() + 50);
}

void Player::onCollision(Person* other) {

}

void Player::update(float dt) {

}
