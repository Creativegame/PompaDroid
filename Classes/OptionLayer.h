#ifndef _OPTIONLAYER_H_
#define _OPTIONLAYER_H_

#include "cocos2d.h"
#include "OptionDelegate.h"
#include "Hero.h"

class OptionLayer : public cocos2d::Layer
{
public:
  OptionLayer();
  ~OptionLayer();

  virtual bool init();
  CREATE_FUNC(OptionLayer);

  bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
  void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
  void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
  void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);

  CC_SYNTHESIZE(OptionDelegate*, _delegator, Delegator);
  

private:
  cocos2d::Point cur_position;

  cocos2d::Sprite *_joyStick;
  cocos2d::Sprite *_joyStick_background;

  void _activeJoyStick(cocos2d::Point position);
  void _inactivityJoyStick();
  void _updateJoyStick(cocos2d::Point direction, float distance);
};

#endif