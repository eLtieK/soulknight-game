#include "ItemFactory.h"
#include "../Objects/Item/Jar.h"

const char* JAR_PATH = "images/items/jar.png";

Item* ItemFactory::createItem(const std::string& type) {
	if (type == "jar") { return new Jar(JAR_PATH); }
	return nullptr;
}