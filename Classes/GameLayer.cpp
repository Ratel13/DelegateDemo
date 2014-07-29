/*
 * GameLayer.cpp
 *
 *  Created on: 2014年7月29日
 *      Author: tubuntu
 */
#include "GameLayer.h"

USING_NS_CC;

GameLayer::GameLayer(){

}
GameLayer::~GameLayer() {

}

bool GameLayer::init() {
	if(!Layer::init()) {
		return false;
	}
	this->gameStatus = GAME_STATUS_READY;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	this->showStartButton();

	return true;
}

void GameLayer::onEnter() {
	Layer::onEnter();

}

void GameLayer::showStartButton() {
	Sprite* startBtn = Sprite::createWithSpriteFrameName("play.png");
	Sprite* startBtnActive = Sprite::createWithSpriteFrameName("play.png");
	startBtn->setScale(0.6f);
	startBtnActive->setScale(0.6f);
	startBtnActive->setPositionY(4);

	auto menuStartItem = MenuItemSprite::create(startBtn,startBtnActive,NULL,
			CC_CALLBACK_1(GameLayer::menuStartCallback,this));
	auto menuStart = Menu::create(menuStartItem,NULL);
	menuStart->setPosition(Vec2(this->visibleSize.width/2,
			this->visibleSize.height/2));
	menuStart->setTag(MENU_START);
	this->addChild(menuStart,10);

}

void GameLayer::menuStartCallback(Ref* pSender) {
	log("callback");
	if(this->gameStatus == GAME_STATUS_OVER) {
		return ;
	}
	if(this->gameStatus == GAME_STATUS_READY) {
		log("start");
		//委托StatusLayer中的onGameStart函数来执行游戏开始逻辑
		this->delegator->onGameStart();
		this->getChildByTag(MENU_START)->runAction(FadeOut::create(0.4f));
		this->removeChildByTag(MENU_START,true);
		this->gameStatus = GAME_STATUS_START;
		this->createSquares();
	} else if(this->gameStatus  == GAME_STATUS_START) {

	}

}

void GameLayer::createSquares(){
	square = Sprite::createWithSpriteFrameName("whitebird.png");
	square->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	square->setColor(Color3B::RED);
	this->addChild(square);
	//游戏开始，5秒后游戏结束
	auto move = MoveTo::create(5.0f,Vec2(square->getPositionX(),origin.y));
	auto moveDone = CallFuncN::create(CC_CALLBACK_1(GameLayer::moveFinished,this));
	auto sequence = Sequence::createWithTwoActions(move,moveDone);
	square->runAction(sequence);
}

void GameLayer::moveFinished(Ref* pSender) {
	//委托StatusLayer中的onGameEnd函数执行游戏结束的逻辑
	this->delegator->onGameEnd();
	this->removeChild(square,true);
}
