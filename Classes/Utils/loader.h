#ifndef __LOADER__
#define __LOADER__

#include <iostream>
#include "cocos2d.h"

const int WINDOW_WIDTH = 1728;
const int WINDOW_HEIGHT = 972;

cocos2d::Animation* createAnimation(const std::string& prefixName, int frameCount, float delay);

#endif