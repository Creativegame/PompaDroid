#include "OptionLayer.h"

OptionLayer::OptionLayer()
{}

OptionLayer::~OptionLayer()
{
  _eventDispatcher->removeAllEventListeners();
}

bool OptionLayer::init()
{
  bool ret = false;

  do {
    CC_BREAK_IF(!Layer::init());

    _joyStick_background = cocos2d::Sprite::create("joystick_bg.png");
    _joyStick_background->setOpacity(100);
    this->addChild(_joyStick_background, 0);
    _joyStick = cocos2d::Sprite::create("joystick.png");
    _joyStick->setOpacity(100);
    this->addChild(_joyStick, 1);
    _inactivityJoyStick();

    auto touch_listener = cocos2d::EventListenerTouchOneByOne::create();
    touch_listener->setSwallowTouches(true);

    touch_listener->onTouchBegan = CC_CALLBACK_2(OptionLayer::onTouchBegan, this);
    touch_listener->onTouchMoved = CC_CALLBACK_2(OptionLayer::onTouchMoved, this);
    touch_listener->onTouchEnded = CC_CALLBACK_2(OptionLayer::onTouchEnded, this);
    touch_listener->onTouchCancelled = CC_CALLBACK_2(OptionLayer::onTouchCancelled, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this);

    ret = true;

  } while (0);

  return ret;
}

bool OptionLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
  cocos2d::Size win_size = cocos2d::Director::getInstance()->getWinSize();

  cocos2d::Point p = touch->getLocation();
  if (p.x <= win_size.width / 2) {        // Left of screen
    _activeJoyStick(p);
  }
  else {                                  // Right of screen
    _delegator->onAttack();
  }

  return true;
}

void OptionLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
  cocos2d::Size win_size = cocos2d::Director::getInstance()->getWinSize();

  const cocos2d::Point start = this->convertToNodeSpace(touch->getStartLocation());
  // If the start point of touching started from right, DO NOTHING.
  if (start.x > win_size.width / 2) {
    return;
  }

  const cocos2d::Point p = this->convertToNodeSpace(touch->getLocation());
  cocos2d::Point direction = (p - start).getNormalized();
  float distance = start.getDistance(p);

  _updateJoyStick(direction, distance);
  _delegator->onWalk(direction, distance);
}

void OptionLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
  _inactivityJoyStick();
  _delegator->onStop();
}

void OptionLayer::onTouchCancelled(cocos2d::Touch *touch,
                                   cocos2d::Event *unused_event)
{}

void OptionLayer::_activeJoyStick(cocos2d::Point position)
{
  _joyStick->setPosition(position);
  _joyStick_background->setPosition(position);
  _joyStick->setVisible(true);
  _joyStick_background->setVisible(true);
}

void OptionLayer::_inactivityJoyStick()
{
  _joyStick->setPosition(_joyStick_background->getPosition());
  _joyStick->setVisible(false);
  _joyStick_background->setVisible(false);
}

void OptionLayer::_updateJoyStick(cocos2d::Point direction, float distance)
{
  cocos2d::log("(%f, %f), %f", direction.x, direction.y, distance);
  cocos2d::Point start = _joyStick_background->getPosition();

  if (distance < 32) {
    _joyStick->setPosition(start + (direction * distance));
  }
  //else if (distance > 96) {
    //_joyStick->setPosition(start + (direction * 64));
  //}
  else {
    _joyStick->setPosition(start + (direction * 32));
  }
}