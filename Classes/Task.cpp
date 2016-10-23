#include "Task.h"
#include "GameScene.h"

USING_NS_CC;
using namespace std;

bool Task::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//各パラメーターの初期化
	int x = random(50, 430);
	int y = random(100, 754);
	switch (random(0, 5))
	{
	case 0:
		this->setTexture("sigoto.png");
		break;
	case 1:
		this->setTexture("kadai.png");
		break;
	case 2:
		this->setTexture("zangyo.png");
		break;
	case 3:
		this->setTexture("report.png");
		break;
	case 4:
		this->setTexture("baito.png");
		break;
	case 5:
		this->setTexture("kaji.png");
		break;
	default:
		break;
	}
	this->setPosition(Vec2(origin.x + x,
		origin.y + y));
	this->setScale(random(0.2f, 0.6f));
	this->setOpacity(0.0f);
	this->runAction(FadeIn::create(1.0f));
	auto seq = Sequence::create(ScaleBy::create(0.5f, 0.5f), ScaleBy::create(0.5f, 2.0f), NULL);
	this->runAction(RepeatForever::create(seq));

	mHP = 10;

	//タッチイベント
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event) {
		auto target = (Sprite*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto parent = (GameScene*)this->getParent()->getParent();

			mHP--;
			if (mHP == 0) {	//HPが0になったら
				this->runAction(Sequence::create(FadeOut::create(1.0f), RemoveSelf::create(), NULL));
				parent->addProgress();
			}

			parent->showPunch(touch->getLocation().x, touch->getLocation().y);

			return true;
		}

		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}