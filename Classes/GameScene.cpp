#include <time.h>

#include "GameScene.h"
#include "Task.h"

USING_NS_CC;

//�V���O���g��
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

	//�x�[�X���Ԃ̏�����
	auto userDefalt = UserDefault::sharedUserDefault();
	int saveTime = userDefalt->getIntegerForKey("saveTime");
	if (saveTime) { 
		mBaseTime = saveTime;
	} else {
		mBaseTime = (int)time(NULL);

		//���Ԃ��L�^
		userDefalt->setIntegerForKey("saveTime", mBaseTime);
		userDefalt->flush();
	}

	//�^�X�N�̐���ǂݍ���
	mTaskNum = userDefalt->getIntegerForKey("taskNum");
	for (int i = 0; i < mTaskNum; i++) {
		auto task = Task::create();
		taskLayer->addChild(task, 2, "task");
	}
	
	//xx�b���ƂɃ^�X�N���o��
	mFreq = 60 * 6;
	//�^�X�N�̏��
	mTaskMax = 50;

	//�V���O���g��
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

		//���Ԃ��L�^
		userDefalt->setIntegerForKey("saveTime", mBaseTime);
		userDefalt->flush();
	}

	//�^�X�N�̐��̈Ⴂ����������
	if (taskLayer->getChildrenCount() != mTaskNum) {
		mTaskNum = taskLayer->getChildrenCount();
		//�^�X�N�̐����L�^
		userDefalt->setIntegerForKey("taskNum", mTaskNum);
		userDefalt->flush();
	}

	Label* timeLabel = (Label*)getChildByName("timeLabel");
	auto sTime = String::createWithFormat("%d", mFreq - dTime);
	timeLabel->setString(sTime->getCString());

}

void GameScene::setBaseTime(int t) { mBaseTime = t; }
