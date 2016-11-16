#pragma once

#include "cocos2d.h"

class Karap {
public:
	Karap();

	std::string getCharaImage();
	std::string getBGImage();
	std::string getFormName();

	std::vector<std::string> getWords(std::string msg);

protected:
	std::string mCharaImage;	//�L�����N�^�[�摜
	std::string mBGImage;		//�w�i�摜
	std::string mFormName;		//�`��

	std::map<std::string, std::vector<std::vector<std::string>>> mWordsMap;	//�������X�g

	std::string mCurrentMsg;	//�ҏW���̃��b�Z�[�W�i���[�U�[����̓��́j
	std::vector<std::vector<std::string>> mCurrentRemark;	//�ҏW���̔���
	std::vector<std::string> mCurrentSpeak;	//�ҏW���̂���


	void setMsg(std::string msg);		//���b�Z�[�W���Z�b�g
	void setWords(std::string words);	//�������Z�b�g
	void addWords();					//������ǉ�
	void addRemark();					//�������X�g��ǉ�
	

};