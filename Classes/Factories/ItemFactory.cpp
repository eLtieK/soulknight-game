#include "ItemFactory.h"
#include "../Objects/Item/Jar.h"
#include "../Objects/Item/Coin.h"

const char* JAR_PATH = "images/items/jar.png";
const char* COIN_PATH = "images/items/coin.png";

Item* ItemFactory::createItem(const std::string& type) {
	if (type == "jar") { return new Jar(JAR_PATH); }
	if (type == "coin") { return new Coin(COIN_PATH); }
	return nullptr;
}