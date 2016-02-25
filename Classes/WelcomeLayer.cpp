#include "WelcomeLayer.h"



bool WelcomeLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibileSize = Director::getInstance()->getVisibleSize();
	auto atlasLoader = AtlasLoader::getInstance();


	//��ȡϵͳʱ��
	time_t t = time(NULL);
	tm* lt = localtime(&t);
	int hour = lt->tm_hour;

	Sprite *bg = nullptr;

	//����ʱ���ȡ����
	if (hour >= 6 && hour <= 17) {
		bg = Sprite::createWithSpriteFrame(atlasLoader->getSpriteFrameByName("bg_day"));
	} else {
		bg = Sprite::createWithSpriteFrame(atlasLoader->getSpriteFrameByName("bg_night"));
	}

	bg->setPosition(visibileSize / 2);
	this->addChild(bg);

	//���½��
	this->land1 = Sprite::createWithSpriteFrame(atlasLoader->getSpriteFrameByName("land"));
	this->land2 = Sprite::createWithSpriteFrame(atlasLoader->getSpriteFrameByName("land"));

	auto landSize = land1->getContentSize();

	this->land1->setPosition(visibileSize.width / 2, landSize.height / 2);
	this->land2->setPosition(visibileSize.width / 2 + landSize.width - 1, landSize.height / 2);

	this->addChild(this->land1);
	this->addChild(this->land2);

	this->schedule(schedule_selector(WelcomeLayer::scroolLand), 0.01f);

	//��ӱ���
	auto title = Sprite::createWithSpriteFrame(atlasLoader->getSpriteFrameByName("title"));
	title->setPosition(visibileSize.width / 2, visibileSize.height / 4 * 3);
	title->setTag(TITLE_TAG);
	this->addChild(title);

	//��Ȩ����
	auto copyRight = Sprite::createWithSpriteFrame(atlasLoader->getSpriteFrameByName("brand_copyright"));
	copyRight->setPosition(visibileSize.width / 2, visibileSize.height / 6);
	copyRight->setTag(COPY_RIGHT_TAG);
	this->addChild(copyRight);


	//��ʼ��ť
	auto startButton = Sprite::createWithSpriteFrame(atlasLoader->getSpriteFrameByName("button_play"));
	auto activeStartButton = Sprite::createWithSpriteFrame(atlasLoader->getSpriteFrameByName("button_play"));
	activeStartButton->setPositionY(5);

	auto menuItem = MenuItemSprite::create(startButton, activeStartButton, NULL, CC_CALLBACK_1(WelcomeLayer::menuCallback, this));
	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(visibileSize.width / 2, visibileSize.height / 3 + 30);
	menu->setTag(MENU_TAG);
	this->addChild(menu);


	//���С��
	this->bird = BirdSprite::getInstance();
	this->bird->createBird();
	this->bird->setTag(BIRD_SPRITE_TAG);
	this->bird->setPosition(visibileSize.width / 2, visibileSize.height / 2 + 30);
	this->bird->idle();
	this->addChild(bird);

	return true;
}

void WelcomeLayer::scroolLand(float delta) {
	if (this->land1->getPositionX() <= 0) {
		this->land1->setPositionX(Director::getInstance()->getVisibleSize().width / 2);
	} else {
		this->land1->setPositionX(this->land1->getPositionX() - 1);
	}
	//fix bug
	this->land2->setPositionX(this->land1->getPositionX() + this->land1->getContentSize().width - 1);
}

void WelcomeLayer::menuCallback(Ref* render) {
	this->removeChildByTag(BIRD_SPRITE_TAG);
	this->removeChildByTag(MENU_TAG);
	this->removeChildByTag(COPY_RIGHT_TAG);
	this->removeChildByTag(TITLE_TAG);

	auto layer = TapLayer::create();
	this->addChild(layer);

}
