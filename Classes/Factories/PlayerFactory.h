#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include "../Objects/Person/Player.h"

class PlayerFactory {
public:
    static Player* createPlayer(const std::string& type);
};

#endif // PLAYER_FACTORY_H
