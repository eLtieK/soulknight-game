#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"
#include "Bullet.h"
#include "../../Utils/loader.h"

class Sword : public Weapon {
public:
    Sword(const std::string& spritePath = "");
    void attack() override;
    void update(float dt) override;

};

#endif // SWORD_H
