#include "speak.h"

#define kModalLayerPriority 1

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
	msgBox->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50));
	msgBox->setOpacity(0.0f);
	msgBox->runAction(FadeIn::create(0.3f));
	msgBox->runAction(MoveBy::create(0.3f, Vec2(0, 50)));
	this->addChild(msgBox, 0, "msgbox");

	auto label1 = Label::createWithTTF("Hello,World!", "fonts/APJapanesefontT.ttf", 24);
	label1->setDimensions(440, 280);
	label1->setTextColor(Color4B::WHITE);
	label1->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	label1->setPosition(Vec2(20, 280));
	this->addChild(label1);
	for (int i = 0; i < label1->getStringLength() + label1->getStringNumLines(); i++) {
		auto AChar = label1->getLetter(i);
		if (nullptr != AChar) {
			AChar->setVisible(false);
			AChar->runAction(
				Sequence::createWithTwoActions(
					DelayTime::create(0.2f*i),
					Show::create()
				));
		}
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);	//優先順位の高いイベントだけを実行する
	listener->onTouchBegan = [&](Touch *touch, Event*event)->bool {
		auto box = this->getChildByName("msgbox");
		box->runAction(FadeOut::create(0.3f));
		this->runAction(Sequence::create(FadeIn::create(0.3f), RemoveSelf::create(), NULL));

		return true;
	};
	auto dip = Director::getInstance()->getEventDispatcher();
	dip->addEventListenerWithSceneGraphPriority(listener, this);
	dip->setPriority(listener, kModalLayerPriority);



	return true;
}