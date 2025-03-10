#ifndef ENEMY_H
#define ENEMY_H

#include "Person.h"

class Enemy : public Person {
public:
    static Enemy* create();
    void update(float dt) override;
    void onCollision(Person* other) override;
};

#endif // ENEMY_H
