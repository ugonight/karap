#pragma execution_character_set("utf-8")

#include <string>

#include "speak.h"
#include "GameScene.h"

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

	auto label1 = Label::createWithTTF("ご苦労だったなガール", "fonts/APJapanesefontT.ttf", 30);
	label1->setDimensions(440, 270);
	label1->setTextColor(Color4B::WHITE);
	label1->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	label1->setPosition(Vec2(20, 270));
	this->addChild(label1, 1, "msg");
	setDelayAnime();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);	//優先順位の高いイベントだけを実行する
	listener->onTouchBegan = CC_CALLBACK_2(Speak::touch, this); 
	auto dip = Director::getInstance()->getEventDispatcher();
	dip->addEventListenerWithSceneGraphPriority(listener, this);
	dip->setPriority(listener, kModalLayerPriority);



	return true;
}

void Speak::setID(std::string id) {
	auto label1 = (Label*)getChildByName("msg");
	if (id == "finish") {
		label1->setString("よく頑張ったな");
	}
	else {
		auto parent = (GameScene*)this->getParent();
		auto karap = parent->getKarap();
		mWords = karap->getWords(id);
		mWordsNum = 0;
		label1->setString(mWords[mWordsNum]);
	}
	setDelayAnime();
}

bool Speak::endCheck() {
	auto label = (Label*)getChildByName("msg");
	for (int i = 0; i < label->getStringLength() + label->getStringNumLines(); i++) {
		auto AChar = label->getLetter(i);
		if (nullptr != AChar) {
			if (AChar->getOpacity() < 255) {
				return false;
			}
		}
	}
	return true;
}

void Speak::setDelayAnime() {
	auto label1 = (Label*)getChildByName("msg");

	for (int i = 0; i < label1->getStringLength() + label1->getStringNumLines(); i++) {
		auto AChar = label1->getLetter(i);
		if (nullptr != AChar) {
			AChar->setOpacity(0.0f);
			AChar->runAction(
				Sequence::createWithTwoActions(
					DelayTime::create(0.1f*i),
					FadeIn::create(0.1f)
				));
		}
	}
}

bool Speak::touch(cocos2d::Touch *touch, cocos2d::Event *event) 
{
	auto label = (Label*)getChildByName("msg");

	if (endCheck()) {	//表示しきっていたら
		if (mWordsNum < mWords.size()-1) {	//会話が終了していなければ
			mWordsNum++;
			label->setString(mWords[mWordsNum]);
			setDelayAnime();
		}
		else {
			auto box = this->getChildByName("msgbox");
			box->runAction(FadeOut::create(0.3f));
			this->runAction(Sequence::create(FadeIn::create(0.3f), RemoveSelf::create(), NULL));
		}
	}
	else {
		for (int i = 0; i < label->getStringLength() + label->getStringNumLines(); i++) {
			auto AChar = label->getLetter(i);
			if (nullptr != AChar) {
				AChar->setOpacity(255);
				AChar->stopAllActions();
			}
		}
	}

	return true;
}