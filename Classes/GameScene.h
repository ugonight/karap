#pragma once

#include "cocos2d.h"

class GameScene : public cocos2d::Layer {
public:
	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(GameScene);

	void setBaseTime(int time);

	static GameScene* sharedGameScene();

private:
	int mBaseTime;	//�A�v���N�����E�o�b�N�O���E���h���ɏ�����
	int mFreq;	//�^�X�N�o���̕p�x
};