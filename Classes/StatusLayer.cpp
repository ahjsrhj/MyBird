#include "StatusLayer.h"



bool StatusLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	this->visibleSize = Director::getInstance()->getVisibleSize();

	this->width = Number::getInstance()->getNumSprite(0)->getContentSize().width;
	this->height = Number::getInstance()->getNumSprite(0)->getContentSize().height;

	this->showScore(0);
	return true;
}

void StatusLayer::showScore(int score) {
	for (auto sprite : numSprites) {
		this->removeChild(sprite);
	}
	//fix bugs
	int bit = 0;
	if (score != 0) {
		bit = log10(score);
	}

	int i = 0;
	do {
		int n = score % 10;
		auto num = Number::getInstance()->getNumSprite(n);
		num->setPosition(this->visibleSize.width / 2
			+ width * (bit + 1) / 2 - width / 2 - i * width,
			visibleSize.height - height / 2);
		this->addChild(num);
		this->numSprites.pushBack(num);
		i++;
		score /= 10;
	}while (score != 0);
}

void StatusLayer::hideScore() {
	
}
