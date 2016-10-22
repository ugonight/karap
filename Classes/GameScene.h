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
	int mBaseTime;	//アプリ起動時・バックグラウンド時に初期化
	int mFreq;	//タスク出現の頻度
	int mTaskMax;	//タスクの上限値
	int mTaskNum;	//表示されているタスクの数
	float mProgress;	//実際の進捗

};