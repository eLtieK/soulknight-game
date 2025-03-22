#include "Sword.h"
#include "../Person/Player.h"
#include "../../Scenes/GameScene.h"

Sword::Sword(const std::string& spritePath) : Weapon(spritePath) {
    this->offset = 10;

}

void Sword::attack() {
    
}

void Sword::update(float dt) {
    this->followMouse(true, false);
}