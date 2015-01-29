#ifndef _OPTIONDELEGATE_H_
#define _OPTIONDELEGATE_H_

#include "cocos2d.h"
#include "Hero.h"

class OptionDelegate
{
public:
  OptionDelegate();
  ~OptionDelegate();

  virtual void onWalk(cocos2d::Point direction, float distance) = 0;
  virtual void onAttack() = 0;
  virtual void onStop() = 0;

private:

};
#endif