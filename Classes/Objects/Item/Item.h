#ifndef ITEM_H
#define ITEM_H

#include "cocos2d.h"
#include "../../Utils/loader.h"

class Item : public cocos2d::Sprite {
public:
    Item(const std::string& spritePath = "", float width = 50, float height = 50);

protected:
};

#endif // ITEM_H
