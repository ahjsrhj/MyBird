#pragma once
#include "cocos2d.h"
#include "WelcomeLayer.h"

using namespace cocos2d;

class WelcomeScene : public Scene {
public:
	WelcomeScene();

	~WelcomeScene();

	virtual bool init();

	CREATE_FUNC(WelcomeScene);
};