#include "Hero.h"

Hero::Hero()
{}

Hero::~Hero()
{}

bool Hero::init()
{
  bool ret = false;
  do
  {
    CC_BREAK_IF(!ActionSprite::initWithSpriteFrameName("hero_idle_00.png"));

    cocos2d::CallFunc *callbackIdle = cocos2d::CallFunc::create(
      std::bind(&Hero::idle, this));

    cocos2d::Animation *idle = createAnimation("hero_idle", 6, 12);
    setIdleAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(idle)));

    cocos2d::Animation *walk = createAnimation("hero_walk", 8, 12);
    setWalkAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(walk)));

    cocos2d::Animation *attack = createAnimation("hero_attack_00", 3, 24);
    setAttackAction(cocos2d::Sequence::create(cocos2d::Animate::create(attack),
      callbackIdle,
      NULL));

    cocos2d::Animation *hurt = createAnimation("hero_hurt", 3, 12);
    setHurtAction(cocos2d::Sequence::create(cocos2d::Animate::create(hurt),
      callbackIdle,
      NULL));

    cocos2d::Animation *knockout = createAnimation("hero_knockout", 5, 12);
    setKnockoutAction(cocos2d::Sequence::create(cocos2d::Animate::create(knockout),
      NULL));

    setATK(20);
    setHP(100);
    setVelocity(1);
    setCenterToBottom(39.0);
    setCenterToSides(29.0);
    setDesiredPosition(this->getPosition());

    ret = true;
  } while (0);

  return ret;
}