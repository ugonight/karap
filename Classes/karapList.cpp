#include"GameScene.h"

USING_NS_CC;
using namespace std;

#define ADD_KARAP(name,clas) mKarapMap[name] = new clas()

void GameScene::initKarapList() {
	ADD_KARAP("nomal", Nomal);
	ADD_KARAP("mafia", Mafia);

}

//Karap* GameScene::getKarap(string mode) {
//	Karap* karap;
//
//	if (mode == "") {
//		karap = new Nomal();
//
//		//ƒ‚[ƒh‚ğ‹L˜^
//		auto userDefalt = UserDefault::getInstance();
//		userDefalt->setStringForKey("mode", "nomal");
//		userDefalt->flush();
//	}
//
//	return karap;
//}