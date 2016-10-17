#pragma once

#include "cocos2d.h"

class GameScene : public cocos2d::Layer {
public:
	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(GameScene);

private:
	int mBaseTime;	//アプリ起動時・バックグラウンド時に初期化
	int mFreq;	//タスク出現の頻度
};