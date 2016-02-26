#pragma once
#include "cocos2d.h"
#include "GameScene.h"
#include "BirdSprite.h"
#include "ControlLayer.h"
#include "BackgroundLayer.h"
#include "SimpleAudioEngine.h"
#include "StatusLayer.h"
#include "WelcomeScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define KEY "best_score"

enum {
	PIPE_PASS,
	PIPE_NEW
};

typedef enum {
	GAME_START,
	GAME_RUNNING,
	GAME_OVER
} GameStatus;

//小鸟刚体的掩码值
const int BIRD_MASK = 1 << 0;

//障碍物刚体的掩码值
const int OBST_MASK = 1 << 1;

//两个管子之间的距离
const int PIPE_DISTANCE = 100;

//管子的高度
const int PIPE_HEIGHT = 320;

//管子宽度
const int PIPE_WIDHT = 52;

//屏幕宽度
const int SCREEN_WIDTH = 288;

//屏幕高度
const int SCREEN_HEIGHT = 512;

//地面高度
const int LAND_HEIGHT = 112;



class GameLayer : public Layer, public ControlDelegate {
public:
	virtual bool init();

	virtual void onTouch();

	virtual void update(float delta);

	//滚动管子
	void scrollPipe(float delta);

	CREATE_FUNC(GameLayer);

	//检测碰撞函数
	bool onContactBegin(const PhysicsContact& contact);


	void bindStatusLayer(StatusLayer * statusLayer);


private:
	//创建管子
	void createPips();

	//获取管子的随机高度
	float getRandomHeight();

	//分数更新
	void checkPass();

	void gameOver();

	//显示分数盘
	void showScorePanel();

private:
	BirdSprite *bird;

	Node *land;

	Node *pipes1;

	Node *pipes2;

	Vector<Node*> pipes;

	float landHeight;

	int score;

	int bestScore;

	StatusLayer *statusLayer;

	Size visibleSize;

	GameStatus gameStatus;

};