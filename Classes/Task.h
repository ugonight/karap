#pragma once

#include "cocos2d.h"

class Task : public cocos2d::Sprite {

public:
	virtual bool init();
	//virtual void update(float delta);

	CREATE_FUNC(Task);

private:
	int mHP;

};