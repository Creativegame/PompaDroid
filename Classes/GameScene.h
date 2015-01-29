#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"
#include "GameLayer.h"
#include "OptionLayer.h"

class GameScene : public cocos2d::Scene
{
public:
    GameScene();
    ~GameScene();

    virtual bool init();
     static cocos2d::Scene* createScene();

    CREATE_FUNC(GameScene);

    CC_SYNTHESIZE(GameLayer*, _gameLayer, GameLayer);
    CC_SYNTHESIZE(OptionLayer*, _optionLayer, OptionLayer);
};

#endif 