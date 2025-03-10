#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"

class Player : public Person {
public:
    static Player* create();
    void jump();
    void update(float dt) override;
    void onCollision(Person* other) override;
};

#endif // PLAYER_H
