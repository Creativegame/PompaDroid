#include "ActionSprite.h"

ActionSprite::ActionSprite()
{
    _idleAction = NULL;
    _walkAction = NULL;
    _attackAction = NULL;
    _hurtAction = NULL;
    _knockoutAction = NULL;
}

ActionSprite::~ActionSprite()
{}

void ActionSprite::update(float dt)
{
  if (getActionState() == ACTION_STATE_WALK) {
    _desiredPosition = this->getPosition();
  }
}

void ActionSprite::idle()
{
    if (_changeState(ACTION_STATE_IDLE)) {
        runAction(_idleAction);
    }
}

void ActionSprite::attack()
{
    if (_changeState(ACTION_STATE_ATTACK)) {
        runAction(_attackAction);
    }
}

void ActionSprite::walk()
{
    if (_changeState(ACTION_STATE_WALK)) {
        runAction(_walkAction);
    }
}

void ActionSprite::hurt()
{
    if (_changeState(ACTION_STATE_HURT)) {
        runAction(_hurtAction);
    }
}

void ActionSprite::knockout()
{
    if (_changeState(ACTION_STATE_KNOCKOUT)) {
        runAction(_knockoutAction);
    }
}

bool ActionSprite::_changeState(ActionState state)
{
    bool ret = false;
    if (_currentState == ACTION_STATE_KNOCKOUT ||
        _currentState == state) {
        return ret;
    }

    this->stopAllActions();
    _currentState = state;
    ret = true;

    return ret;
}

cocos2d::Animation *ActionSprite::createAnimation(const char *fmt,
                                         int count,
                                         float fps)
{
    cocos2d::Vector<cocos2d::SpriteFrame*> frames(count);

    for (int i = 0; i < count; i++) {
        const char *png = cocos2d::String::createWithFormat("%s_%02d.png", fmt, i)->getCString();
        cocos2d::log(png);
        cocos2d::SpriteFrame *frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
        frames.pushBack(frame);
    }

    return cocos2d::Animation::createWithSpriteFrames(frames, 1 / fps);
}