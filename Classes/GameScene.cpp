#include <time.h>

#include "GameScene.h"
#include "Task.h"

USING_NS_CC;

//シングルトン
static GameScene* instanceOfGameScene;

GameScene *GameScene::sharedGameScene() {

	return instanceOfGameScene;
}


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

	auto timeLabel = Label::createWithTTF("Hello World", "fonts/APJapanesefontT.ttf", 24);
	timeLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	timeLabel->setPosition(Vec2(origin.x + 10,
		origin.y + visibleSize.height - timeLabel->getContentSize().height));
	timeLabel->setColor(Color3B::BLUE);
	this->addChild(timeLabel, 1, "timeLabel");

	//ベース時間の初期化
	auto userDefalt = UserDefault::sharedUserDefault();
	int saveTime = userDefalt->getIntegerForKey("saveTime");
	if (saveTime) { 
		mBaseTime = saveTime;
	} else {
		mBaseTime = (int)time(NULL);

		//時間を記録
		auto userDefalt = UserDefault::sharedUserDefault();
		userDefalt->setIntegerForKey("saveTime", mBaseTime);
		userDefalt->flush();
	}
	
	//xx秒ごとにタスクが出現
	mFreq = 600;

	//シングルトン
	instanceOfGameScene = this;

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

		//時間を記録
		auto userDefalt = UserDefault::sharedUserDefault();
		userDefalt->setIntegerForKey("saveTime", mBaseTime);
		userDefalt->flush();

	}



	Label* timeLabel = (Label*)getChildByName("timeLabel");
	auto sTime = String::createWithFormat("%d", dTime);
	timeLabel->setString(sTime->getCString());

}

void GameScene::setBaseTime(int t) { mBaseTime = t; }
