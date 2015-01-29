#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include "cocos2d.h"
#include "ActionSprite.h"
#include "Hero.h"
#include "Robots.h"
#include "OptionDelegate.h"

class GameLayer : public cocos2d::Layer, public OptionDelegate
{
public:
  GameLayer();
  ~GameLayer();

  virtual bool init();
  CREATE_FUNC(GameLayer);

  void onWalk(cocos2d::Point direction, float distance);
  void onAttack();
  void onStop();

  void update(float dt);

  void setViewpointCenter(cocos2d::Point position);

private:
  cocos2d::TMXTiledMap* _map;
  ActionSprite *_hero;
  cocos2d::Vector<Robot *> _robots;
  cocos2d::SpriteBatchNode *_actors;
  cocos2d::Point _heroVelocity;
};

#endif