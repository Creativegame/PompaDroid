#include "Robots.h"

Robot::Robot() {}

Robot::~Robot() {}

bool Robot::init()
{
  bool ret;

  do
  {
    CC_BREAK_IF(!ActionSprite::initWithSpriteFrameName("robot_idle_00.png"));

    cocos2d::CallFunc *callbackIdle = cocos2d::CallFunc::create(
      std::bind(&Robot::idle, this));

    cocos2d::Animation *idle = createAnimation("robot_idle", 5, 12);
    setIdleAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(idle)));

    cocos2d::Animation *walk = createAnimation("robot_walk", 6, 20);
    setWalkAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(walk)));

    cocos2d::Animation *attack = createAnimation("robot_attack", 5, 12);
    setAttackAction(cocos2d::Sequence::create(cocos2d::Animate::create(attack),
      callbackIdle,
      NULL));

    cocos2d::Animation *hurt = createAnimation("robot_hurt", 3, 12);
    setHurtAction(cocos2d::Sequence::create(cocos2d::Animate::create(hurt),
      callbackIdle,
      NULL));

    cocos2d::Animation *knockout = createAnimation("robot_knockout", 5, 12);
    setKnockoutAction(cocos2d::Sequence::create(cocos2d::Animate::create(knockout),
      NULL));

    setATK(20);
    setHP(100);
    setVelocity(1);
    setDirection(cocos2d::Point::ZERO);

    ret = true;
  } while (0);

  return ret;
}