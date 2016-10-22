#pragma once

#include "cocos2d.h"

class GameScene : public cocos2d::Layer {
public:
	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(GameScene);

	void setBaseTime(int time);

	//static GameScene* sharedGameScene();

	void showPunch(int x, int y);
	void addProgress();

private:
	int mBaseTime;	//�A�v���N�����E�o�b�N�O���E���h���ɏ�����
	int mFreq;	//�^�X�N�o���̕p�x
	int mTaskMax;	//�^�X�N�̏���l
	int mTaskNum;	//�\������Ă���^�X�N�̐�
	float mProgress;	//���ۂ̐i��

};