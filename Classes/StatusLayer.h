/*
 * StatusLayer.h
 *
 *  Created on: 2014年7月29日
 *      Author: tubuntu
 */

#ifndef STATUSLAYER_H_
#define STATUSLAYER_H_
#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

const int SPRITE_TITLE_TAG = 1000;
/**
 * StatusDelegate 是委托类的父类，在GameLayer中实现三个虚函数
 * 具体代码如下
 * class StatusDelegate {
 *	public:
 *		virtual void onGameStart() = 0;
 *		virtual void onGamePlaying() = 0;
 *		virtual void onGameEnd() = 0;
 *	};
 */
class StatusLayer : public Layer ,public StatusDelegate{
public:
	StatusLayer(void);
	~StatusLayer(void);

	virtual bool init();
	CREATE_FUNC(StatusLayer);

	//实现父类StatusDelegate的三个虚函数
	void onGameStart();//游戏开始逻辑判断函数
	void onGamePlaying();//游戏运行逻辑判断函数
	void onGameEnd();//游戏结束逻辑判断函数

private:

	void moveFinished(Ref* pSender);//title精灵移动结束后回调此函数
	void showRestartMenu(Ref* pSender);//显示重新开始按钮
	void showOverSprite();//显示GameOver精灵函数
	void menuRestartCallback(cocos2d::Ref* pSender);//点击开始按钮后回调此函数
	void menuShareCallback(cocos2d::Ref* pSender);//分享按钮回调按钮

private:
	Size visibleSize;
	Point origin;
	Sprite* gameOverSprite;
};




#endif /* STATUSLAYER_H_ */
