#include "GameLayer.h"



bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	this->score = 0;

	visibleSize = Director::getInstance()->getVisibleSize();

	//创建小鸟
	this->bird = BirdSprite::getInstance();
	this->bird->createBird();
	//创建物理属性
	PhysicsBody *body = PhysicsBody::createCircle(15);
	//设置为受到重力影响的动态刚体
	body->setDynamic(true);
	//设置线性阻尼
	body->setLinearDamping(0.0f);
	//设置刚体是否受物理世界重力的影响
	body->setGravityEnable(false);
	//设置形状的恢复系数
	//body->getShape(0)->setRestitution(0.0f);
	body->getShape(0)->setDensity(1.0f);
	//设置所属种类的掩码值
	body->setCategoryBitmask(BIRD_MASK);
	body->setCollisionBitmask(BIRD_MASK | OBST_MASK);
	body->setContactTestBitmask(BIRD_MASK | OBST_MASK);
	this->bird->setPhysicsBody(body);
	this->bird->setPosition(visibleSize.width / 3, visibleSize.height / 2);
	this->bird->idle();
	this->bird->fly();
	this->addChild(this->bird, 2);


	//添加陆地物理属性
	auto land = Node::create();
	landHeight = BackgroundLayer::getLandHeight();
	auto landBody = PhysicsBody::createBox(Size(visibleSize.width, landHeight));
	landBody->getShape(0)->setRestitution(0.0f);
	landBody->setDynamic(false);
	landBody->setGravityEnable(false);
	landBody->setCategoryBitmask(OBST_MASK);
	landBody->setCollisionBitmask(BIRD_MASK | OBST_MASK);
	landBody->setContactTestBitmask(BIRD_MASK | OBST_MASK);
	land->setPhysicsBody(landBody);
	land->setPosition(visibleSize.width / 2, landHeight / 2);
	this->addChild(land, 10);

	//添加碰撞监听
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);


	this->createPips();

	this->scheduleUpdate();
	this->schedule(schedule_selector(GameLayer::scrollPipe), 0.01f);
	return true;
	
}

void GameLayer::onTouch() {
	this->bird->getPhysicsBody()->setVelocity(Vec2(0, 280));
}

void GameLayer::update(float delta) {
	float verticalSpeed = this->bird->getPhysicsBody()->getVelocity().y;
	this->bird->setRotation(-verticalSpeed * 0.1f);
	this->checkPass();

}

void GameLayer::scrollPipe(float delta) {
	for (Node *singlePipe : this->pipes) {
		float posX = singlePipe->getPositionX();
		if ((posX -= 2) <= -PIPE_WIDHT / 2) {
			posX = SCREEN_WIDTH + PIPE_WIDHT / 2;
			auto h = this->getRandomHeight();
			singlePipe->setPositionY(this->getRandomHeight());

			singlePipe->setTag(PIPE_NEW);


		}
		singlePipe->setPositionX(posX);
	}

}

bool GameLayer::onContactBegin(const PhysicsContact& contact) {

	log("onContactBegin");
	this->gameOver();

	return true;

}


void GameLayer::createPips() {
	for (int i = 0; i < 2; i++) {
		auto pipeUp = Sprite::createWithSpriteFrame(
			AtlasLoader::getInstance()->getSpriteFrameByName("pipe_up"));
		auto pipeDown = Sprite::createWithSpriteFrame(
			AtlasLoader::getInstance()->getSpriteFrameByName("pipe_down"));

		pipeUp->setPosition(Vec2(0, -(PIPE_HEIGHT + PIPE_DISTANCE) / 2));
		pipeDown->setPosition(Vec2(0, (PIPE_HEIGHT + PIPE_DISTANCE) / 2));

		//创建物理属性
		auto pipeUpBody = PhysicsBody::createBox(pipeUp->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT, Vec2::ZERO);
		//设置为静态刚体
		pipeUpBody->setDynamic(false);
		pipeUpBody->getShape(0)->setRestitution(0.0f);
		//设置刚体密度
		pipeUpBody->getShape(0)->setDensity(1.0f);
		pipeUpBody->setCategoryBitmask(OBST_MASK);
		pipeUpBody->setCollisionBitmask(BIRD_MASK | OBST_MASK);
		pipeUpBody->setContactTestBitmask(BIRD_MASK | OBST_MASK);
		pipeUp->setPhysicsBody(pipeUpBody);

		auto pipeDownBody = PhysicsBody::createBox(pipeDown->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT, Vec2::ZERO);
		//设置为静态刚体
		pipeDownBody->setDynamic(false);
		pipeDownBody->getShape(0)->setRestitution(0.0f);
		pipeDownBody->getShape(0)->setDensity(1.0f);
		//设置碰撞掩码
		pipeDownBody->setCategoryBitmask(OBST_MASK);
		pipeDownBody->setCollisionBitmask(BIRD_MASK | OBST_MASK);
		pipeDownBody->setContactTestBitmask(BIRD_MASK | OBST_MASK);

		pipeDown->setPhysicsBody(pipeDownBody);

		auto singlePipe = Node::create();
		singlePipe->addChild(pipeUp);
		singlePipe->addChild(pipeDown);

		if (i == 0) {
			singlePipe->setPosition(Vec2(SCREEN_WIDTH * 2 + PIPE_WIDHT / 2, 250));
		} else {
			singlePipe->setPosition(Vec2(SCREEN_WIDTH * 2.5f + PIPE_WIDHT, this->getRandomHeight()));
		}

		singlePipe->setTag(PIPE_NEW);

		this->addChild(singlePipe);
		this->pipes.pushBack(singlePipe);
	}

}

float GameLayer::getRandomHeight() {
	return LAND_HEIGHT + 50 + PIPE_DISTANCE / 2 + (rand() % (SCREEN_HEIGHT - LAND_HEIGHT - 100))  / 2;
}

void GameLayer::checkPass() {
	for (auto pipe : this->pipes) {
		if (pipe->getTag() == PIPE_NEW && pipe->getPositionX() < this->bird->getPositionX()) {
			this->score++;
			this->statusLayer->showScore(score);
			SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");

			pipe->setTag(PIPE_PASS);
		}
	}
}

void GameLayer::gameOver() {
	this->unscheduleAllCallbacks();
	this->removeChild(this->bird);
	for (auto pipe : this->pipes) {
		this->removeChild(pipe);
	}
	this->statusLayer->hideScore();
	this->showScorePanel();
}

void GameLayer::showScorePanel() {
	auto panel = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("score_panel"));
	panel->setPosition(Director::getInstance()->getVisibleSize() / 2);
	this->addChild(panel);

	auto scoreNode = Number::getInstance()->getNumNodeWithNumber(this->score);
	scoreNode->setPosition(panel->getContentSize().width / 5 * 4, panel->getContentSize().height / 3 * 2);
	panel->addChild(scoreNode);

	auto gameOverSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_game_over"));
	gameOverSprite->setPosition(visibleSize.width / 2, visibleSize.height / 3 * 2);
	this->addChild(gameOverSprite);
}

void GameLayer::bindStatusLayer(StatusLayer * statusLayer) {
	this->statusLayer = statusLayer;

}
