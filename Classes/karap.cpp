#pragma execution_character_set("utf-8")

#include<string>
#include<map>
#include<vector>

#include "karap.h"

USING_NS_CC;
using namespace std;

Karap::Karap() : mCharaImage(""), mBGImage("") , mCurrentMsg("default") {}

string Karap::getCharaImage() { return mCharaImage; }
string Karap::getBGImage() { return mBGImage; }

vector<string> Karap::getWords(string msg) {
	//検索
	string key = "default";
	for (auto itr = mWordsMap.begin(); itr != mWordsMap.end(); ++itr) {
		if (msg.find(itr->first) != -1) {
			key = itr->first;
			break;
		}
	}
	auto wordsList = mWordsMap[key];
	return wordsList.at(random(0, (int)wordsList.size() - 1));
}

void Karap::setMsg(string msg){
	mCurrentMsg = msg;
}

void Karap::setWords(string words) {
	mCurrentSpeak.push_back(words);
}

void Karap::addWords() {
	mCurrentRemark.push_back(mCurrentSpeak);
	mCurrentSpeak.clear();
}

void Karap::addRemark() {
	mWordsMap[mCurrentMsg] = mCurrentRemark;
	mCurrentRemark.clear();
}