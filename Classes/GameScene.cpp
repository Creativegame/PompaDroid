#include "GameScene.h"

USING_NS_CC;
using namespace cocos2d;

GameScene::GameScene()
{}

GameScene::~GameScene()
{}

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    bool ret = false;

    do {
        CC_BREAK_IF(!Scene::init());
        _gameLayer = GameLayer::create();
        _optionLayer = OptionLayer::create();
        _optionLayer->setDelegator(_gameLayer);

        this->addChild(_gameLayer, 0);
        this->addChild(_optionLayer, 1);

        ret = true;
    } while (0);

    return ret;
}