#include "WakeUpSceneFactory.h"
#include "GameScene.h"

USING_NS_CC;

cocos2d::Scene* WakeUpSceneFactory::create() {

	auto scene = Scene::create();

	auto *layer = GameScene::create();
	scene->addChild(layer, 1, "game");

	return scene;
}