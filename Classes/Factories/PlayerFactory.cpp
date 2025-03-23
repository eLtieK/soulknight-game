#include "Factories/PlayerFactory.h"
const char* PLAYER_PATH = "images/Player/down/1.png";

Player* PlayerFactory::createPlayer(const std::string& type) {
    return new Player(PLAYER_PATH);
}
