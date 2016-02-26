#include "Number.h"


Number *Number::sharedNumber = nullptr;

Number *Number::getInstance() {
	if (sharedNumber == nullptr) {
		sharedNumber = new Number();
		if (!sharedNumber->init()) {
			delete sharedNumber;
			sharedNumber = nullptr;
			log("create failed!");
		}
	}

	return sharedNumber;
}

bool Number::init() {
	for (int i = 0; i <= 9; i++) {
		auto num = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(StringUtils::format("number_score_0%d", i).c_str()));
		//log(StringUtils::format("number_score_0%d", i).c_str());

		this->numbers.pushBack(num);

		auto smallNum = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(StringUtils::format("number_context_0%d", i).c_str()));
		this->smallNumbers.pushBack(smallNum);
	}

	return true;
}

cocos2d::Sprite *Number::getNumSprite(int num) {
	return this->numbers.at(num);
}

cocos2d::Node* Number::getNumNodeWithNumber(int num) {
	auto node = Node::create();
	do{
		int n = num % 10;



	} while (num != 0);

	return node;
}
