#pragma once
#include "cocos2d.h"
#include "Number.h"

using namespace cocos2d;

class StatusLayer : public Layer {
public:
	virtual bool init();

	CREATE_FUNC(StatusLayer);

	void showScore(int score);

	void hideScore();

private:
	Vector<Sprite*> numSprites;

	Size visibleSize;

	int width;
	int height;

};
