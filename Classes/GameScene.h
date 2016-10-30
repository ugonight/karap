#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "karapList.h"

class GameScene : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate {
public:
	virtual bool init();
	virtual void update(float delta);



	CREATE_FUNC(GameScene);

	void setBaseTime(int time);

	//static GameScene* sharedGameScene();

	void showPunch(int x, int y);
	void addProgress();
	Karap* getKarap();

private:
	int mBaseTime;	//アプリ起動時・バックグラウンド時に初期化
	std::string mMode;	//カラぴの形態
	Karap* mKarap;	//カラぴクラス
	int mFreq;	//タスク出現の頻度
	int mTaskMax;	//タスクの上限値
	int mTaskNum;	//表示されているタスクの数
	float mProgress;	//実際の進捗
	bool mPunch;	//showPunchが一フレームに一回だけ読み込まれるようにする
	bool mInput;	//入力フォームが表示されているか

	bool karapTouch(cocos2d::Touch *touch, cocos2d::Event *event);	//カラぴタッチイベント
	bool InputCancel(cocos2d::Touch *touch, cocos2d::Event *event);	//入力キャンセル
	bool InputEnter(cocos2d::Touch *touch, cocos2d::Event *event);	//入力終了

	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);

	void InputEnd();	//入力終了処理
	void InputHide();	//入力フォームを消す

	Karap* getKarap(std::string);	//karapList.cppに実装
};