#pragma once
#include "cocos2d.h"

using namespace cocos2d;


class ControlDelegate {
public:
	virtual void onTouch() = 0;
};



class ControlLayer : public Layer {
public:
	virtual bool init();

	CREATE_FUNC(ControlLayer);

	bool onTouchBegan(Touch *touch, Event *unused_event);

protected:
	CC_SYNTHESIZE(ControlDelegate*, delegate, Deletage);

};
