#include "WelcomeScene.h"

WelcomeScene::WelcomeScene() { }

WelcomeScene::~WelcomeScene() { }

bool WelcomeScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto layer = WelcomeLayer::create();
	this->addChild(layer);

	return true;
}
