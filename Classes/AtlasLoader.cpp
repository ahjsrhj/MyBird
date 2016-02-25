#include "AtlasLoader.h"


AtlasLoader * AtlasLoader::sharedInstance = nullptr;

AtlasLoader * AtlasLoader::getInstance() {
	if (sharedInstance == nullptr) {
		sharedInstance = new AtlasLoader();
	}

	return sharedInstance;
}

void AtlasLoader::destroyInstance() {
	CC_SAFE_DELETE(sharedInstance);
}

void AtlasLoader::loadAtlas(string filename, Texture2D *texture) {
	string data = FileUtils::getInstance()->getStringFromFile(filename);
	unsigned pos;
	Atlas atlas;
	pos = data.find_first_of("\n");
	string line = data.substr(0, pos);
	data = data.substr(pos + 1);
	while (line != "") {
		sscanf(line.c_str(), "%s %d %d %f %f %f %f", atlas.name, &atlas.width, &atlas.height, &atlas.start.x, &atlas.start.y, &atlas.end.x, &atlas.end.y);
		atlas.start.x *= 1024;
		atlas.start.y *= 1024;
		atlas.end.x *= 1024;
		atlas.end.y *= 1024;

		pos = data.find_first_of("\n");
		line = data.substr(0, pos);
		data = data.substr(pos + 1);

		//fix bug
		if (atlas.name == string("land")) {
			atlas.start.x += 1;
		}

		Rect rect = Rect(atlas.start.x, atlas.start.y, atlas.width, atlas.height);
		auto frame = SpriteFrame::createWithTexture(texture, rect);
		this->_spriteFrames.insert(string(atlas.name), frame);
	}

}

cocos2d::SpriteFrame * AtlasLoader::getSpriteFrameByName(string name) {
	return this->_spriteFrames.at(name);
}

