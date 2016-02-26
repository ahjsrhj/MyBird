#pragma once
#include "cocos2d.h"
#include "AtlasLoader.h"

using namespace cocos2d;

class Number {
public:
	static Number *getInstance();
	
	bool init();

	Sprite *getNumSprite(int num);

	Node* getNumNodeWithNumber(int num);

private:
	static Number *sharedNumber;

	Vector<Sprite*> numbers;

	Vector<Sprite*> smallNumbers;

};