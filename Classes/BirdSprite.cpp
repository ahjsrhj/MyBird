#include "BirdSprite.h"


BirdSprite * BirdSprite::sharedInstance = nullptr;

BirdSprite * BirdSprite::getInstance() {
	if (sharedInstance == nullptr) {
		sharedInstance = new BirdSprite();
		if (!sharedInstance->init()) {
			delete sharedInstance;
			sharedInstance = nullptr;
			log("Error:BirdSprite init Faild!");
		}
	}

	return sharedInstance;

}

bool BirdSprite::init() {
	this->isFirst = 1;

	return true;
}

bool BirdSprite::createBird() {
	this->createBirdByRandom();
	if (Sprite::initWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(this->birdName))) {

		auto animation = this->createAnimation(this->birdNameFormat.c_str(), 3, 10);
		auto animate = Animate::create(animation);
		this->idleAction = RepeatForever::create(animate);

		auto up = CCMoveBy::create(0.4f, Point(0, 8));
		auto upBack = up->reverse();
		this->swingAction = RepeatForever::create(Sequence::create(up, upBack, NULL));

		return true;
	} else {
		return false;
	}

}

void BirdSprite::idle() {
	if (changeState(ACTION_STATE_IDLE)) {
		this->runAction(this->idleAction);
		this->runAction(this->swingAction);
	}
}

void BirdSprite::fly() {
	if (changeState(ACTION_STATE_FLY)) {
		this->stopAction(this->swingAction);
		this->getPhysicsBody()->setGravityEnable(true);
	}
}

void BirdSprite::die() {
	if (changeState(ACTION_STATE_DIE)) {
		this->stopAllActions();
	}
}

cocos2d::Animation * BirdSprite::createAnimation(const char *fmt, int count, float fps) {
	auto animation = Animation::create();
	animation->setDelayPerUnit(1 / fps);
	for (int i = 0; i < count; i++) {
		const char *filename = String::createWithFormat(fmt, i)->getCString();
		auto frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	return animation;
}

void BirdSprite::createBirdByRandom() {
	if (isFirst == 1) {
		isFirst = 2;
	} else if (isFirst == 2) {
		isFirst = 1;
		return;
	}

	srand(time(NULL));
	int type = rand() % 3;
	switch (type) {
	case 0:
		this->birdName = "bird0_0";
		this->birdNameFormat = "bird0_%d";
		break;
	case 1:
		this->birdName = "bird1_0";
		this->birdNameFormat = "bird1_%d";
		break;
	case 2:
		this->birdName = "bird2_0";
		this->birdNameFormat = "bird2_%d";
		break;
	}
}


bool BirdSprite::changeState(ActionState state) {
	this->currentState = state;
	return true;
}
