#pragma once

#include "cocos2d.h"

class Speak : public cocos2d::Layer {
public:
	virtual bool init();
	//virtual void update(float delta);

	void setID(std::string id = "");	//メッセージとかモード分けとか

	CREATE_FUNC(Speak);

private:
	std::vector<std::string> mWords;	//発言
	int mWordsNum;						//発言番号
	std::string mID;					//id

	bool touch(cocos2d::Touch *touch, cocos2d::Event *event);

	bool endCheck();	//メッセージが表示しきっているか
	void setDelayAnime();	//文字送りさせる
};