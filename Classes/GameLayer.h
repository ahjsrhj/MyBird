#pragma once
#include "cocos2d.h"
#include "GameScene.h"
#include "BirdSprite.h"
#include "ControlLayer.h"
#include "BackgroundLayer.h"
#include "SimpleAudioEngine.h"
#include "StatusLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

enum {
	PIPE_PASS,
	PIPE_NEW
};

//С����������ֵ
const int BIRD_MASK = 1 << 0;

//�ϰ�����������ֵ
const int OBST_MASK = 1 << 1;

//��������֮��ľ���
const int PIPE_DISTANCE = 100;

//���ӵĸ߶�
const int PIPE_HEIGHT = 320;

//���ӿ��
const int PIPE_WIDHT = 52;

//��Ļ���
const int SCREEN_WIDTH = 288;

//��Ļ�߶�
const int SCREEN_HEIGHT = 512;

//����߶�
const int LAND_HEIGHT = 112;



class GameLayer : public Layer, public ControlDelegate {
public:
	virtual bool init();

	virtual void onTouch();

	virtual void update(float delta);

	//��������
	void scrollPipe(float delta);

	CREATE_FUNC(GameLayer);

	//�����ײ����
	bool onContactBegin(const PhysicsContact& contact);


	void bindStatusLayer(StatusLayer * statusLayer);

private:
	//��������
	void createPips();

	//��ȡ���ӵ�����߶�
	float getRandomHeight();

	//��������
	void checkPass();

	void gameOver();
private:
	BirdSprite *bird;

	Node *land;

	Node *pipes1;

	Node *pipes2;

	Vector<Node*> pipes;

	float landHeight;

	int score;

	StatusLayer *statusLayer;

};