#include "WeaponFactory.h"
const char* GUN_PATH = "images/items/gun.png";
const char* SWORD_PATH = "images/items/sword.png";

Weapon* WeaponFactory::createWeapon(const std::string& type) {
    if (type == "gun") {
        return new Gun(GUN_PATH);
    }
    else if (type == "sword") {
        return new Sword(SWORD_PATH);
    }
    return nullptr;
}
