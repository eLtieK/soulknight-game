#include "Factories/PlayerFactory.h"
const char* PLAYER_PATH = "images/Player/down/1.png";

Player* PlayerFactory::createPlayer(const std::string& type) {
    /*if (type == "zombie") {
        return Player::create("zombie.png", 100, 10);
    }
    else if (type == "robot") {
        return Player::create("robot.png", 200, 20);
    }*/
    return new Player(PLAYER_PATH);
}
