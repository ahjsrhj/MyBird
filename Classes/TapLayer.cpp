#include "TapLayer.h"



bool TapLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto tap = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("tutorial"));
	tap->setPosition(Director::getInstance()->getVisibleSize() / 2);
	this->addChild(tap);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch *touch, Event *event) {
		auto scene = GameScene::create();
		auto transition = TransitionFade::create(1.0f, scene);
		Director::getInstance()->replaceScene(transition);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}
