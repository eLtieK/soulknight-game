#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include "../Objects/Item/Item.h"

class ItemFactory {
public:
    static Item* createItem(const std::string& type);
};

#endif // ITEM_FACTORY_H
