#ifndef ENEMY_H
#define ENEMY_H

#include "Person.h"


class Enemy : public Person {
public:
    Enemy(const std::string& spritePath = "");
    void update(float dt) override;
    void onCollision(Person* other) override;
    void move(float dt) override;
};

#endif // ENEMY_H
