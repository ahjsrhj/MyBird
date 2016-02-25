#pragma once
#include "cocos2d.h"
#include "AtlasLoader.h"

using namespace cocos2d;


class BackgroundLayer : public Layer {
public:
	virtual bool init();
	CREATE_FUNC(BackgroundLayer);

	void scrollLand(float delta);

	static float getLandHeight();

private:
	Sprite *land1;
	Sprite *land2;
};