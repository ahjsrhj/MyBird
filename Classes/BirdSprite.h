#pragma once
#include "cocos2d.h"
#include "AtlasLoader.h"

using namespace cocos2d;
using namespace std;

typedef enum {
	ACTION_STATE_IDLE,
	ACTION_STATE_FLY,
	ACTION_STATE_DIE
} ActionState;

const int BIRD_SPRITE_TAG = 10000;

class BirdSprite : public Sprite {
public:
	static BirdSprite *getInstance();
	
	virtual bool init();

	bool  createBird();

	void idle();

	void fly();

	void die();

protected:
	static Animation *createAnimation(const char *fmt, int count, float fps);

	void createBirdByRandom();

private:
	static BirdSprite *sharedInstance;

	bool changeState(ActionState state);

	ActionState currentState;

	string birdName;

	string birdNameFormat;

	Action *idleAction;

	Action *swingAction;

	int isFirst;

};