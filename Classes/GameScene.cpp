#include "GameScene.h"



bool GameScene::init() {
	if (!Scene::initWithPhysics()) {
		return false;
	}

	//ÏÔÊ¾ÎïÀíÂÖÀª
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);


	//Ìí¼Ó±³¾°²ã
	auto backgroundLayer = BackgroundLayer::create();
	if (backgroundLayer) {
		this->addChild(backgroundLayer);
	}
	this->getPhysicsWorld()->setGravity(Vec2(0, -900));

	auto statusLayer = StatusLayer::create();

	auto gameLayer = GameLayer::create();
	if (gameLayer) {
		this->addChild(gameLayer);
		gameLayer->bindStatusLayer(statusLayer);
	}

	this->addChild(statusLayer);

	auto controlLayer = ControlLayer::create();
	if (controlLayer) {
		controlLayer->setDeletage(gameLayer);
		this->addChild(controlLayer);
	}





	return true;
}
