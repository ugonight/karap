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
	std::string mCharaImage;	//キャラクター画像
	std::string mBGImage;		//背景画像
	std::string mFormName;		//形態

	std::map<std::string, std::vector<std::vector<std::string>>> mWordsMap;	//発言リスト

	std::string mCurrentMsg;	//編集中のメッセージ（ユーザーからの入力）
	std::vector<std::vector<std::string>> mCurrentRemark;	//編集中の発言
	std::vector<std::string> mCurrentSpeak;	//編集中のｒｙ


	void setMsg(std::string msg);		//メッセージをセット
	void setWords(std::string words);	//発言をセット
	void addWords();					//発言を追加
	void addRemark();					//発言リストを追加
	

};