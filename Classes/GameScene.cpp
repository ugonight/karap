#pragma execution_character_set("utf-8")

#include <time.h>

#include "GameScene.h"
#include "Task.h"
#include "speak.h"

USING_NS_CC;
using namespace ui;

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

	auto userDefalt = UserDefault::getInstance();

	initKarapList();	//カラぴマップ初期化

	//モード読み込み
	mForm = userDefalt->getStringForKey("form");
	//mKarap = getKarap(mMode);
	if (mForm == "") {
		mKarap = mKarapMap["nomal"];
		//モードを記録
		auto userDefalt = UserDefault::getInstance();
		userDefalt->setStringForKey("form", "nomal");
		userDefalt->flush();
	}
	else {
		mKarap = mKarapMap[mForm];
	}

	//背景
	//auto back = Sprite::create("room.png");
	auto back = Sprite::create(mKarap->getBGImage());
	back->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(back, 0, "back");

	//カラぴ
	//auto karap = Sprite::create("nomal.png");
	auto karap = Sprite::create(mKarap->getCharaImage());
	karap->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(karap, 1, "karap");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::karapTouch, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, karap);

	//タスクを表示させるレイヤー
	auto taskLayer = Layer::create();

	this->addChild(taskLayer, 2, "taskLayer");

	//セリフを表示させるレイヤー
	//auto speakLayer = Speak::create();
	//this->addChild(speakLayer, 5, "speakLayer");


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
	addChild(percentTxt, 7, "progressText");

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
	}
	else {
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
	//showPunchが呼び出されているか
	mPunch = 0;
	//入力フォームが表示されているか
	mInput = 0;

	//シングルトン
	//instanceOfGameScene = this;

	return true;
}

void GameScene::update(float delta) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto userDefalt = UserDefault::getInstance();

	int dTime = (int)time(NULL) - mBaseTime;
	auto taskLayer = this->getChildByName("taskLayer");

	mPunch = 0;

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

	auto percentTxt = (Label*)this->getChildByName("progressText");
	if (mProgress >= 100.0f) {	//100％になったとき
		percentTxt->setString("Completed!");
		auto speakLayer = Speak::create();
		this->addChild(speakLayer, 5, "speakLayer");
		speakLayer->setID("finish");
		mProgress = 0.0f;
	}

	Label* timeLabel = (Label*)getChildByName("timeLabel");
	auto sTime = String::createWithFormat("%d, %d", mFreq - dTime, mTaskNum);
	timeLabel->setString(sTime->getCString());

}

void GameScene::setBaseTime(int t) { mBaseTime = t; }

void GameScene::showPunch(int x, int y) {
	if (!mPunch) {
		mPunch = 1;
		auto punch = Sprite::create("punch.png");
		punch->setPosition(Vec2(x, y));
		punch->setOpacity(0.0f);
		punch->setScale(0.5f);
		auto seq1 = Sequence::create(FadeIn::create(0.2f), FadeOut::create(0.2f), RemoveSelf::create(), NULL);
		punch->runAction(seq1);
		punch->runAction(ScaleBy::create(0.4f, 2.0f));
		this->addChild(punch, 3, "punch");
	}
}

void GameScene::addProgress() {
	auto userDefalt = UserDefault::getInstance();

	mProgress += 1.0f;
	auto percentTxt = (Label*)this->getChildByName("progressText");
	percentTxt->setString(String::createWithFormat("%d%%", (int)mProgress)->getCString());
	//進捗を記録
	userDefalt->setFloatForKey("progress", mProgress);
	userDefalt->flush();
}

bool GameScene::karapTouch(Touch *touch, Event *event) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto target = (Sprite*)event->getCurrentTarget();
	Rect targetBox = target->getBoundingBox();
	Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);

	if (targetBox.containsPoint(touchPoint))
	{
		if (mTaskNum == 0 && mInput == 0) {	//タスク無しでカラぴをタップしたら

			mInput = 1;

			auto editFrame = Sprite::create("inputf.png");
			editFrame->setPosition(Vec2(origin.x + visibleSize.width / 2,
				origin.y + visibleSize.height / 2));
			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);
			listener->onTouchBegan = CC_CALLBACK_2(GameScene::InputCancel, this);
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, editFrame);
			editFrame->setOpacity(0.0f);
			editFrame->runAction(FadeIn::create(0.2f));
			this->addChild(editFrame, 9, "editFrame");
			auto editLabel = Label::createWithTTF("唐松にメッセージを送りましょう", "fonts/APJapanesefontT.ttf", 24);
			editLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
				origin.y + visibleSize.height / 2 + 100));
			editLabel->setColor(Color3B::BLACK);
			editLabel->setOpacity(0.0f);
			editLabel->runAction(FadeIn::create(0.2f));
			this->addChild(editLabel, 10, "editLabel");
			auto editButton = Sprite::create("enter.png");
			editButton->setPosition(Vec2(origin.x + visibleSize.width / 2,
				origin.y + visibleSize.height / 2 - 80));
			auto listener2 = EventListenerTouchOneByOne::create();
			listener2->onTouchBegan = CC_CALLBACK_2(GameScene::InputEnter, this);
			listener2->setSwallowTouches(true);
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, editButton);
			editButton->setOpacity(0.0f);
			editButton->runAction(FadeIn::create(0.2f));
			this->addChild(editButton, 10, "editButton");
			auto editBox = EditBox::create(Size(340, 60), "inputb.png");
			editBox->setFont("fonts/APJapanesefontT.ttf", 32);
			editBox->setPlaceHolder("ひらがな10文字以内");
			editBox->setFontColor(Color4B(0, 0, 0, 255));
			editBox->setMaxLength(100);
			editBox->setText("");
			editBox->setReturnType(EditBox::KeyboardReturnType::DONE);
			editBox->setInputMode(EditBox::InputMode::SINGLE_LINE);
			editBox->setPosition(Vec2(origin.x + visibleSize.width / 2,
				origin.y + visibleSize.height / 2 + 20));
			editBox->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			editBox->setDelegate(this);
			editBox->setOpacity(0.0f);
			editBox->runAction(FadeIn::create(0.2f));
			this->addChild(editBox, 10, "editBox");


		}
		return true;
	}

	return false;
}

void GameScene::editBoxEditingDidBegin(EditBox* editBox) {
}

void GameScene::editBoxEditingDidEnd(EditBox* editBox) {
}

void GameScene::editBoxTextChanged(EditBox* editBox, const std::string& text) {
}

void GameScene::editBoxReturn(EditBox* editBox) {
}

bool GameScene::InputCancel(Touch *touch, Event *event) {
	auto target = (Sprite*)event->getCurrentTarget();
	Rect targetBox = target->getBoundingBox();
	Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);

	if (!targetBox.containsPoint(touchPoint) && mInput)	//枠外をタップしたら
	{
		InputHide();

		return true;
	}

	return false;
}

bool GameScene::InputEnter(Touch *touch, Event *event) {
	auto target = (Sprite*)event->getCurrentTarget();
	Rect targetBox = target->getBoundingBox();
	Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);

	if (targetBox.containsPoint(touchPoint) && mInput)
	{
		InputEnd();
		return true;
	}

	return false;
}

void GameScene::InputEnd() {
	InputHide();
	auto speakLayer = Speak::create();
	auto editBox = (EditBox*)this->getChildByName("editBox");
	this->addChild(speakLayer, 5, "speakLayer");
	speakLayer->setID(editBox->getText() );
}

void GameScene::InputHide() {
	mInput = 0;

	auto editFrame = this->getChildByName("editFrame");
	auto editLabel = this->getChildByName("editLabel");
	auto editButton = this->getChildByName("editButton");
	auto editBox = this->getChildByName("editBox");

	editFrame->runAction(Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(), NULL));
	editLabel->runAction(Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(), NULL));
	editButton->runAction(Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(), NULL));
	editBox->runAction(Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(), NULL));
}

Karap* GameScene::getKarap(){
	return mKarap;
}

void GameScene::changeForm() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto white = Sprite::create("white.png");
	white->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	white->setOpacity(0.0f);
	white->runAction(Sequence::create(FadeIn::create(0.5f),CallFunc::create(CC_CALLBACK_0(GameScene::chageForm2,this)),NULL));
	this->addChild(white, 20, "white");
}

void GameScene::chageForm2() {
	auto pTimer = (ProgressTimer*)this->getChildByName("progress");
	auto percentTxt = (Label*)this->getChildByName("progressText");
	auto userDefalt = UserDefault::getInstance();

	//次のフォームを決める
	bool loop = 1;
	while (loop) {
		int num = random(0, (int)mKarapMap.size() - 1), i = 0;
		for (auto itr = mKarapMap.begin(); itr != mKarapMap.end(); ++itr) {
			if (i == num) {
				if (itr->first == mForm) {
					break;	//前と同じならやりなおし
				}
				else {
					loop = 0;
					mForm = itr->first;
					mKarap = itr->second;
					//モードを記録
					userDefalt->setStringForKey("form", mForm);
					break;
				}
			}
			i++;
		}
	}

	auto back = (Sprite*)this->getChildByName("back");
	back->setTexture(mKarap->getBGImage());
	auto karap = (Sprite*)this->getChildByName("karap");
	karap->setTexture(mKarap->getCharaImage());

	//mProgress = 0.0f;
	pTimer->setPercentage(0.0f);
	percentTxt->setString("0%%");
	//進捗を記録
	userDefalt->setFloatForKey("progress", mProgress);
	userDefalt->flush();

	auto white = (Sprite*)getChildByName("white");
	white->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), NULL));
}
