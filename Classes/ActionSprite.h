#ifndef _ACTIONSPRITE_H_
#define _ACTIONSPRITE_H_

#include "cocos2d.h"

typedef enum
{
  ACTION_STATE_NONE = 0,
  ACTION_STATE_IDLE,
  ACTION_STATE_WALK,
  ACTION_STATE_ATTACK,
  ACTION_STATE_HURT,
  ACTION_STATE_KNOCKOUT,
} ActionState;

class ActionSprite : public cocos2d::Sprite
{
public:
  ActionSprite();
  ~ActionSprite();

  void update(float dt);

  void idle();
  void walk();
  void attack();
  void hurt();
  void knockout();

  // 定义每个状态动作的get/set方法
  CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _idleAction, IdleAction);
  CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _attackAction, AttackAction);
  CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _hurtAction, HurtAction);
  CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _knockoutAction, KnockoutAction);
  CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _walkAction, WalkAction);

  CC_SYNTHESIZE(float, _centerToSides, CenterToSides);
  CC_SYNTHESIZE(float, _centerToBottom, CenterToBottom);
  CC_SYNTHESIZE(cocos2d::Vec2, _desiredPosition, DesiredPosition);

  CC_SYNTHESIZE(ActionState, _currentState, ActionState);
  CC_SYNTHESIZE(float, _velocity, Velocity);     // Current Velocity
  CC_SYNTHESIZE(cocos2d::Point, _direction, Direction);   // Moving direction.(Vector)
  CC_SYNTHESIZE(unsigned int, _hp, HP);                   // HP
  CC_SYNTHESIZE(unsigned int, _atk, ATK);                 // Attack



protected:
  static cocos2d::Animation *createAnimation(const char *fmt, int count, float fps);

private:
  bool _changeState(ActionState state);

};
#endif