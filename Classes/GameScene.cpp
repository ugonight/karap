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

	auto taskLayer = Layer::create();
	this->addChild(taskLayer, 2, "taskLayer");

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
		userDefalt->setIntegerForKey("saveTime", mBaseTime);
		userDefalt->flush();
	}

	//タスクの数を読み込む
	mTaskNum = userDefalt->getIntegerForKey("taskNum");
	for (int i = 0; i < mTaskNum; i++) {
		auto task = Task::create();
		taskLayer->addChild(task, 2, "task");
	}
	
	//xx秒ごとにタスクが出現
	mFreq = 60 * 6;
	//タスクの上限
	mTaskMax = 50;

	//シングルトン
	instanceOfGameScene = this;

	return true;
}

void GameScene::update(float delta) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto userDefalt = UserDefault::sharedUserDefault();

	int dTime = (int)time(NULL) - mBaseTime;
	auto taskLayer = this->getChildByName("taskLayer");

	if (dTime >= mFreq) {
		for (int i = 0; i < dTime / mFreq && taskLayer->getChildrenCount() < mTaskMax; i++) {
			auto task = Task::create();
			taskLayer->addChild(task, 2, "task");
		}
		mBaseTime = (int)time(NULL) - dTime % mFreq;

		//時間を記録
		userDefalt->setIntegerForKey("saveTime", mBaseTime);
		userDefalt->flush();
	}

	//タスクの数の違いがあったら
	if (taskLayer->getChildrenCount() != mTaskNum) {
		mTaskNum = taskLayer->getChildrenCount();
		//タスクの数を記録
		userDefalt->setIntegerForKey("taskNum", mTaskNum);
		userDefalt->flush();
	}

	Label* timeLabel = (Label*)getChildByName("timeLabel");
	auto sTime = String::createWithFormat("%d", mFreq - dTime);
	timeLabel->setString(sTime->getCString());

}

void GameScene::setBaseTime(int t) { mBaseTime = t; }
