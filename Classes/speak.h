#pragma once

#include "cocos2d.h"

class Speak : public cocos2d::Layer {
public:
	virtual bool init();
	//virtual void update(float delta);

	void setID(std::string id = "");	//���b�Z�[�W�Ƃ����[�h�����Ƃ�

	CREATE_FUNC(Speak);

private:
	bool endCheck();	//���b�Z�[�W���\���������Ă��邩
	void setDelayAnime();	//�������肳����
};