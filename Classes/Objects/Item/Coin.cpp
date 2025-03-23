#include "Coin.h"

Coin::Coin(const std::string& spritePath) : Item(spritePath) {
	this->setScale(0.3f);
}