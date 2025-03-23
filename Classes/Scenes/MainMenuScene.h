#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "../Layers/AboutLayer.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    void onAbout(cocos2d::Ref* sender);
    virtual bool init();
    CREATE_FUNC(MainMenuScene);
};

#endif // __MAIN_MENU_SCENE_H
