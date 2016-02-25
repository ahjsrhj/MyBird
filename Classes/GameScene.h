#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "GameLayer.h"
#include "ControlLayer.h"
#include "StatusLayer.h"

using namespace cocos2d;

class GameScene : public Scene {
public:
	virtual bool init();

	CREATE_FUNC(GameScene);

};