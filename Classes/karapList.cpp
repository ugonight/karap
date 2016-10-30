#include"GameScene.h"

USING_NS_CC;
using namespace std;

Karap* GameScene::getKarap(string mode) {
	Karap* karap;

	if (mode == "nomal") {
		karap = new Nomal();
	}
	else {
		karap = new Nomal();

		//ƒ‚[ƒh‚ğ‹L˜^
		auto userDefalt = UserDefault::getInstance();
		userDefalt->setStringForKey("mode", "nomal");
		userDefalt->flush();
	}

	return karap;
}