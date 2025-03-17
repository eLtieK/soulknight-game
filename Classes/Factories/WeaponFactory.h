#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include "../Objects/Weapon/Gun.h"
#include "../Objects/Weapon/Sword.h"

class WeaponFactory {
public:
    static Weapon* createWeapon(const std::string& type);
};

#endif // WEAPON_FACTORY_H
