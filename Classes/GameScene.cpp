#include <time.h>

#include "GameScene.h"
#include "Task.h"
#include "speak.h"

USING_NS_CC;

//シングルトン
//static GameScene* instanceOfGameScene;
//
//GameScene *GameScene::sharedGameScene() {
//
//	return instanceOfGameScene;
//}


bool GameScene::init() {
	if (Layer::init() == false)
		return false;

	this->scheduleUpdate();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto userDefalt = UserDefault::sharedUserDefault();

	//背景
	auto back = Sprite::create("room.png");
	back->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(back, 0, "back");

	//カラぴ
	auto karap = Sprite::create("nomal.png");
	karap->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(karap, 1, "karap");

	//タスクを表示させるレイヤー
	auto taskLayer = Layer::create();
	this->addChild(taskLayer, 2, "taskLayer");

	//セリフを表示させるレイヤー
	auto speakLayer = Speak::create();
	this->addChild(speakLayer, 5, "speakLayer");


	//進捗状況を読み込む
	mProgress = 0.0f;
	mProgress = userDefalt->getFloatForKey("progress");

	//進捗
	auto pFrame = Sprite::create("progress.png");
	pFrame->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	pFrame->setPosition(Vec2(origin.x + 20, origin.y + visibleSize.height - 50));
	addChild(pFrame, 6, "pFrame");
	auto progressBar = Sprite::create("sintyoku.png");
	auto pTimer = ProgressTimer::create(progressBar);
	pTimer->setPercentage(0.0f);
	pTimer->setType(kCCProgressTimerTypeBar);
	pTimer->setBarChangeRate(Vec2(1, 0));
	pTimer->setMidpoint(Vec2(0, 0));
	pTimer->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	pTimer->setPosition(Vec2(origin.x + 20, origin.y + visibleSize.height - 50));
	addChild(pTimer, 7, "progress");
	pTimer->setPercentage(mProgress);

	//パーセント表示用テキスト
	auto percentTxt = Label::createWithTTF(String::createWithFormat("%d%%", (int)mProgress)->getCString(), "fonts/APJapanesefontT.ttf", 20);
	percentTxt->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	percentTxt->setColor(Color3B::BLACK);
	percentTxt->setPosition(Vec2(pTimer->getPositionX(), pTimer->getPositionY() - 30));
	addChild(percentTxt, 7,"progressText");

	auto timeLabel = Label::createWithTTF("Hello World", "fonts/APJapanesefontT.ttf", 24);
	timeLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	timeLabel->setPosition(Vec2(origin.x + 10,
		origin.y + visibleSize.height - timeLabel->getContentSize().height));
	timeLabel->setColor(Color3B::BLUE);
	this->addChild(timeLabel, 1, "timeLabel");

	//ベース時間の初期化
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
	//instanceOfGameScene = this;

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

	auto pTimer = (ProgressTimer*)this->getChildByName("progress");
	float percent = pTimer->getPercentage();
	if (percent < mProgress) {
		//プログレスバーを進める
		pTimer->setPercentage(percent + 0.1);
	}

	Label* timeLabel = (Label*)getChildByName("timeLabel");
	auto sTime = String::createWithFormat("%d, %d", mFreq - dTime, mTaskNum);
	timeLabel->setString(sTime->getCString());

}

void GameScene::setBaseTime(int t) { mBaseTime = t; }

void GameScene::showPunch(int x, int y) {
	auto punch = Sprite::create("punch.png");
	punch->setPosition(Vec2(x, y));
	punch->setOpacity(0.0f);
	punch->setScale(0.5f);
	auto seq1 = Sequence::create(FadeIn::create(0.2f), FadeOut::create(0.2f), RemoveSelf::create(), NULL);
	punch->runAction(seq1);
	punch->runAction(ScaleBy::create(0.4f, 2.0f));
	this->addChild(punch, 3, "punch");
}

void GameScene::addProgress() {
	auto userDefalt = UserDefault::sharedUserDefault();

	mProgress += 1.0f;
	auto percentTxt = (Label*)this->getChildByName("progressText");
	percentTxt->setString(String::createWithFormat("%d%%", (int)mProgress)->getCString());
	//進捗を記録
	userDefalt->setFloatForKey("progress", mProgress);
	userDefalt->flush();

	if (mProgress >= 100.0f) {
		percentTxt->setString("Completed!");
	}
}