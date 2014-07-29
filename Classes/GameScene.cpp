/*
 * GameScene.cpp
 *
 *  Created on: 2014年7月29日
 *      Author: tubuntu
 */
#include "GameScene.h"
#include "GameLayer.h"
#include "StatusLayer.h"

USING_NS_CC;

GameScene::GameScene(){

}

GameScene::~GameScene(){

}

bool GameScene::init() {
	if(Scene::init()) {
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("flappyrec.plist","flappyrec.png");

		auto statusLayer = StatusLayer::create();
		this->addChild(statusLayer);

		//Add the main game layer
		auto gameLayer = GameLayer::create();
		gameLayer->setDelegator(statusLayer);
		this->addChild(gameLayer);


		return true;
	} else {
		return false;
	}
}

