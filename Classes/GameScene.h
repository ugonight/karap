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
	int mBaseTime;	//�A�v���N�����E�o�b�N�O���E���h���ɏ�����
	std::string mMode;	//�J���҂̌`��
	Karap* mKarap;	//�J���҃N���X
	int mFreq;	//�^�X�N�o���̕p�x
	int mTaskMax;	//�^�X�N�̏���l
	int mTaskNum;	//�\������Ă���^�X�N�̐�
	float mProgress;	//���ۂ̐i��
	bool mPunch;	//showPunch����t���[���Ɉ�񂾂��ǂݍ��܂��悤�ɂ���
	bool mInput;	//���̓t�H�[�����\������Ă��邩

	bool karapTouch(cocos2d::Touch *touch, cocos2d::Event *event);	//�J���҃^�b�`�C�x���g
	bool InputCancel(cocos2d::Touch *touch, cocos2d::Event *event);	//���̓L�����Z��
	bool InputEnter(cocos2d::Touch *touch, cocos2d::Event *event);	//���͏I��

	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);

	void InputEnd();	//���͏I������
	void InputHide();	//���̓t�H�[��������

	Karap* getKarap(std::string);	//karapList.cpp�Ɏ���
};