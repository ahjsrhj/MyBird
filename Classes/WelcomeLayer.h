#pragma once
#include "cocos2d.h"
#include "BirdSprite.h"
#include "GameScene.h"
#include "TapLayer.h"

using namespace cocos2d;

const int MENU_TAG = 10001;

const int COPY_RIGHT_TAG = 10002;

const int TITLE_TAG = 10003;


class WelcomeLayer : public Layer {
public:
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);

	void scroolLand(float delta);

	void menuCallback(Ref* render);

private:
	Sprite *land1;
	Sprite *land2;
	BirdSprite *bird;
};