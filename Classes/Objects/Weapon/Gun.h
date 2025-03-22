#ifndef GUN_H
#define GUN_H

#include "Weapon.h"
#include "Bullet.h"
#include "../../Utils/loader.h"

class Gun : public Weapon {
public:
    Gun(const std::string& spritePath = "");
    void attack() override;

};

#endif // GUN_H
