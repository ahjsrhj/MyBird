#pragma once
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;



typedef struct _atlas {
	char name[255];
	int width;
	int height;
	Point start;
	Point end;
} Atlas;

class AtlasLoader {
public:
	static AtlasLoader *getInstance();
	static void destroyInstance();

	void loadAtlas(string filename, Texture2D *texture);

	SpriteFrame *getSpriteFrameByName(string name);


protected:
	static AtlasLoader *sharedInstance;

	Map<std::string, SpriteFrame*> _spriteFrames;

};