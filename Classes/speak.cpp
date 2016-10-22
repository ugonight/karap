#include "speak.h"

USING_NS_CC;

bool Speak::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto msgBox = Sprite::create("msg.png");
	msgBox->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(msgBox, 0, "msgbox");

	return true;
}