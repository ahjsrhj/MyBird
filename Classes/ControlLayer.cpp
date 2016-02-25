#include "ControlLayer.h"



bool ControlLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(ControlLayer::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;

}

bool ControlLayer::onTouchBegan(Touch *touch, Event *unused_event) {
	delegate->onTouch();

	return true;
}
