#pragma once

#include "cocos2d.h"

class Speak : public cocos2d::Layer {
public:
	virtual bool init();
	//virtual void update(float delta);

	CREATE_FUNC(Speak);

private:
	bool endCheck();	//メッセージが表示しきっているか
};