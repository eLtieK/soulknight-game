#include "WeaponFactory.h"
const char* GUN_PATH = "images/gun.png";

Weapon* WeaponFactory::createWeapon(const std::string& type) {
    if (type == "gun") {
        return new Gun(GUN_PATH);
    }
   /* else if (type == "sword") {
        return new Sword();
    }*/
    return nullptr;
}
