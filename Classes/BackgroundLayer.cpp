#include "BackgroundLayer.h"



bool BackgroundLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	time_t t = time(NULL);
	tm* lt = localtime(&t);
	int hour = lt->tm_hour;
	std::string name;
	if (hour >= 6 && hour <= 17) {
		name = "bg_day";
	} else {
		name = "bg_night";
	}

	auto bg = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(name));
	bg->setPosition(Director::getInstance()->getVisibleSize() / 2);
	this->addChild(bg);

	this->land1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->land2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));

	this->land1->setPosition(visibleSize.width / 2, land1->getContentSize().height / 2);
	this->land2->setPosition(
		visibleSize.width / 2 + land1->getContentSize().width - 1, 
		land1->getContentSize().height / 2);
	land1->setGlobalZOrder(1);
	land2->setGlobalZOrder(1);

	this->addChild(this->land1);
	this->addChild(this->land2);


	this->schedule(schedule_selector(BackgroundLayer::scrollLand), 0.01f);

	return true;
}

void BackgroundLayer::scrollLand(float delta) {
	int pos = this->land1->getPositionX();
	if (pos <= 0) {
		pos = Director::getInstance()->getVisibleSize().width / 2;
	} else {
		pos -= 2;
	}
	this->land1->setPositionX(pos);
	//fix bug land Æ«ÒÆÒ»¸öÏñËØ
	this->land2->setPositionX(pos + land1->getContentSize().width - 1);

}

float BackgroundLayer::getLandHeight() {
	return Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"))->getContentSize().height;

}
