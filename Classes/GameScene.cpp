#include <time.h>

#include "GameScene.h"
#include "Task.h"

USING_NS_CC;

bool GameScene::init() {
	if (Layer::init() == false)
		return false;

	this->scheduleUpdate();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto back = Sprite::create("room.png");
	back->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(back, 0, "back");

	auto karap = Sprite::create("nomal.png");
	karap->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(karap, 1, "karap");

	//ベース時間の初期化
	mBaseTime = (int)time(NULL);
	//xx秒ごとにタスクが出現
	mFreq = 30;


	return true;
}

void GameScene::update(float delta) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int dTime = (int)time(NULL) - mBaseTime;


	if (dTime >= mFreq) {
		for (int i = 0; i < dTime / mFreq; i++) {
			auto task = Task::create();
			//auto task = Sprite::create("task/sigoto.png");
			//int x = random(50, 430);
			//int y = random(100,754);
			//task->setPosition(Vec2(origin.x + x,
			//	origin.y + y));
			//task->setScale(random(0.2f,0.6f));
			//task->setOpacity(0.0f);
			//task->runAction(FadeIn::create(1.0f));
			//auto seq = Sequence::create(ScaleBy::create(0.5f, 0.5f), ScaleBy::create(0.5f, 2.0f), NULL);
			//task->runAction(RepeatForever::create(seq));
			this->addChild(task, 2);
		}
		mBaseTime = (int)time(NULL);
	}
}