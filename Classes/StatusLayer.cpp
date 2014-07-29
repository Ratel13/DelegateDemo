/*
 * StatusLayer.cpp
 *
 *  Created on: 2014年7月29日
 *      Author: tubuntu
 */
#include "StatusLayer.h"
#include "GameScene.h"

USING_NS_CC;

StatusLayer::StatusLayer() {
}

StatusLayer::~StatusLayer() {
}

bool StatusLayer::init() {
	if(!Layer::init()) {
		return false;
	}
	//获取屏幕大小和原点坐标
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	//添加游戏中的背景
	Sprite* background = Sprite::createWithSpriteFrameName("flappyrec_welcome_bg.png");
	background->setPosition(Point::ZERO);
	background->setAnchorPoint(Point::ZERO);
	this->addChild(background);

	//添加游戏中的标题
	Sprite* title = Sprite::createWithSpriteFrameName("flappyrec_welcome_title.png");
	title->setPosition(Vec2(0-title->getContentSize().width,visibleSize.height*4/5));
	title->setTag(SPRITE_TITLE_TAG);//设置tag值
	this->addChild(title);

	auto move = MoveTo::create(1.0f,Vec2(visibleSize.width/2-50,title->getPositionY()));
	//移动结束后回调此函数
	auto moveDone = CallFuncN::create(CC_CALLBACK_1(StatusLayer::moveFinished,this));
	//先加速后减速的动画特效
	EaseExponentialOut* sineIn = EaseExponentialOut::create(move);
	//序列动画
	auto sequence = Sequence::createWithTwoActions(sineIn,moveDone);
	title->runAction(sequence);

	return true;
}

/**
 * title移动结束后调用此函数
 */
void StatusLayer::moveFinished(Ref* pSender) {
	//TODO
}

/**
 * 委托类的方法，此方法会在GameLayer中被调用，用于游戏的开始
 */
void StatusLayer::onGameStart(){
	this->getChildByTag(SPRITE_TITLE_TAG)->runAction(FadeOut::create(0.4f));
}

/**
 * 委托类的方法，此方法会在GameLayer中被调用，用于游戏的运行中的逻辑实现
 */
void StatusLayer::onGamePlaying(){
	//TODO
}

/**
 * 委托类的方法，此方法会在GameLayer中被调用，用于游戏的结束逻辑的实现
 */
void StatusLayer::onGameEnd(){
	this->showOverSprite();

}
/**
 * gameOverSprite精灵的添加，并添加从下到上出现的动作，
 * 动作结束后调用显示按钮的函数
 */
void StatusLayer::showOverSprite() {

	gameOverSprite = Sprite::createWithSpriteFrameName("flappyrec_welcome_rec.png");
	gameOverSprite->setPosition(Vec2(visibleSize.width / 2,0-gameOverSprite->getContentSize().height));
	gameOverSprite->setScale(0.5f);
	this->addChild(gameOverSprite);

	auto move = MoveTo::create(0.8f ,Vec2(visibleSize.width/2,visibleSize.height/2 + 60));
	auto moveDone = CallFuncN::create(CC_CALLBACK_1(StatusLayer::showRestartMenu,this));
	EaseExponentialOut* sineIn = EaseExponentialOut::create(move);
	Sequence* sequence = Sequence::createWithTwoActions(sineIn,moveDone);

	gameOverSprite->runAction(sequence);
}
/**
 * 按钮显示的回调函数，显示开始和分享按钮
 * 并为按钮设置回调函数
 */
void StatusLayer::showRestartMenu(Ref* pSender) {

	Node* tmpNode = Node::create();//两个按钮的父节点

	Sprite* restartBtn = Sprite::createWithSpriteFrameName("play.png");
	Sprite* restartBtnActive = Sprite::createWithSpriteFrameName("play.png");
	restartBtn->setScale(0.6f);//缩放
	restartBtnActive->setScale(0.6f);//缩放
	restartBtnActive->setPositionY(-4);//先下移动四个单位

	auto menuRestartItem = MenuItemSprite::create(restartBtn,restartBtnActive,NULL,
			CC_CALLBACK_1(StatusLayer::menuRestartCallback,this));//设置按钮回调函数
	auto menuRestart = Menu::create(menuRestartItem,NULL);
	menuRestart->setPosition(Vec2(this->visibleSize.width/2 - 35,
			this->visibleSize.height/2 - gameOverSprite->getContentSize().height/3 + 60.0f));
	tmpNode->addChild(menuRestart);//将按钮添加到父节点中

	Sprite* shareBtn = Sprite::createWithSpriteFrameName("share.png");
	Sprite* shareBtnActive = Sprite::createWithSpriteFrameName("share.png");
	shareBtn->setScale(0.6f);
	shareBtnActive->setScale(0.6f);
	shareBtnActive->setPositionY(-4);

	auto menuShareItem = MenuItemSprite::create(shareBtn,shareBtnActive,NULL,
			CC_CALLBACK_1(StatusLayer::menuShareCallback,this));//分享按钮的会点函数
	auto menuShare = Menu::create(menuShareItem,NULL);
	menuShare->setPosition(Point(this->visibleSize.width/2 + 65,
			this->visibleSize.height/2 - gameOverSprite->getContentSize().height/3 + 60.0f));
	tmpNode->addChild(menuShare);

	this->addChild(tmpNode);//添加父节点
	auto fadeIn = FadeIn::create(0.1f);//0.1s后显示出现
	tmpNode->runAction(fadeIn);//父节点执行动作
}

/**
 * 重新开始按钮的回调函数，再次开始游戏
 */
void StatusLayer::menuRestartCallback(cocos2d::Ref* pSender){
    auto scene = GameScene::create();
    TransitionScene *transition = TransitionFade::create(1, scene);
    Director::getInstance()->replaceScene(transition);
}
/**
 * 分享按钮的回调函数
 */
void StatusLayer::menuShareCallback(cocos2d::Ref* pSender){
	//TODO
}
