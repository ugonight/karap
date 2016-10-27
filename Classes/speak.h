#pragma once

#include "cocos2d.h"

class Speak : public cocos2d::Layer {
public:
	virtual bool init();
	//virtual void update(float delta);

	void setID(std::string id = "");	//メッセージとかモード分けとか

	CREATE_FUNC(Speak);

private:
	bool endCheck();	//メッセージが表示しきっているか
	void setDelayAnime();	//文字送りさせる
};