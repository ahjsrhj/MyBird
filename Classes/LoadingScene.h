#pragma once
#include "cocos2d.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "WelcomeScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

class LoadingScene : public Layer {
public:
	LoadingScene();
	~LoadingScene();

	static Scene *createScene();

	virtual bool init();

	virtual void onEnter();

	CREATE_FUNC(LoadingScene);

	void LoadingCallback(Texture2D *texture);

};