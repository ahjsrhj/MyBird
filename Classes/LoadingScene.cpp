#include "LoadingScene.h"



LoadingScene::LoadingScene() { }

LoadingScene::~LoadingScene() { }

cocos2d::Scene * LoadingScene::createScene() {
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init() {
	if (!Layer::init()) {
		return false;
	}

	auto bg = Sprite::create("splash.png");
	bg->setPosition(Director::getInstance()->getVisibleSize() / 2);
	this->addChild(bg);

	Director::getInstance()->getTextureCache()->addImageAsync("atlas.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));

	return true;
}

void LoadingScene::onEnter() {
	
}

void LoadingScene::LoadingCallback(Texture2D *texture) {
	AtlasLoader::getInstance()->loadAtlas("atlas.txt", texture);

	SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");  
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");  
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");  
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");  
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");  

	auto scene = WelcomeScene::create();
	auto transition = TransitionFade::create(1.0f, scene);
	Director::getInstance()->replaceScene(transition);
	
}

