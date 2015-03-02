#include "GameLayer.h"

using namespace cocos2d;

GameLayer::GameLayer()
{
    _map = NULL;
}

GameLayer::~GameLayer()
{
  this->unscheduleUpdate();
}

bool GameLayer::init()
{
    bool ret = false;

    do {
        CC_BREAK_IF(!Layer::init());

        // Initialize the tile map.
        _map = TMXTiledMap::create("./Sprites/pd_tilemap.tmx");
        this->addChild(_map);
        
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./Sprites/pd_sprites.plist");
        _actors = cocos2d::SpriteBatchNode::create("./Sprites/pd_sprites.pvr.ccz");
        this->addChild(_actors);

        _hero = Hero::create();
        _hero->setPosition(cocos2d::Point(80, 80));
        _hero->idle();

        _actors->addChild(_hero);

        for (int i = 0; i < 5; i++) {
            Robot *robot = Robot::create();
            robot->setPosition(cocos2d::Point(CCRANDOM_0_1() * 400, CCRANDOM_0_1() * 100));
            robot->idle();
            _robots.pushBack(robot);
            _actors->addChild(robot);
        }

        this->scheduleUpdate();
        ret = true;
    } while (0);

    return ret;
}

void GameLayer::onAttack()
{
  _hero->attack();
}

void GameLayer::onWalk(cocos2d::Point direction, float distance)
{
  _hero->setFlippedX(direction.x < 0 ? true : false);
  _heroVelocity = direction * (distance < 32 ? 1 : 2);
  _hero->walk();

}

void GameLayer::onStop()
{
  _hero->idle();
}

void GameLayer::update(float dt)
{
  _hero->update(dt);
  if (_hero->getActionState() == ACTION_STATE_WALK) {
    //CCLOG("map_size: %f, tile_size: %f", _map->getMapSize(), _map->getTileSize());
    //CCLOG("_hero.x: %f, _hero.y: %f", _hero->getPosition().x, _hero->getPosition().y);

    // _hero->setPosition(_hero->getPosition() + _heroVelocity);
    float posX = MIN(_map->getMapSize().width * _map->getTileSize().width - _hero->getCenterToSides(),
                     MAX(_hero->getCenterToSides(), (_hero->getPosition() + _heroVelocity).x));
    float posY = MIN(3 * _map->getTileSize().height + _hero->getCenterToBottom(),
                     MAX(_hero->getCenterToBottom(), (_hero->getPosition() + _heroVelocity).y));
    _hero->setPosition(posX, posY);
  }
  this->setViewpointCenter(_hero->getPosition());
}


void GameLayer::setViewpointCenter(cocos2d::Point position)
{
  cocos2d::Size win_size = cocos2d::Director::getInstance()->getWinSize();

  int x = MAX(position.x, win_size.width / 2);
  int y = MAX(position.y, win_size.height / 2);

  x = MIN(x, (_map->getMapSize().width * _map->getTileSize().width) - win_size.width / 2);
  y = MIN(y, (_map->getMapSize().width * _map->getTileSize().width) - win_size.width / 2);
  
  cocos2d::Point actualPos(x, y);

  cocos2d::Point centerOfView(win_size.width / 2, win_size.height / 2);
  cocos2d::Point viewPoint = centerOfView - actualPos;

  this->setPosition(viewPoint);
}