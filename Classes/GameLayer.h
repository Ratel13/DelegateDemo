/*
 * GameLayer.h
 *
 *  Created on: 2014年7月29日
 *      Author: tubuntu
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_
#include "cocos2d.h"

USING_NS_CC;

typedef enum _game_status {
	GAME_STATUS_READY = 1,
	GAME_STATUS_START,
	GAME_STATUS_OVER
} GameStatus;


class StatusDelegate {
public:
	/**
	* When the game start, this method will be called
	*/
	virtual void onGameStart() = 0;

	/**
	* During paying, after the score changed, this method will be called
	*/
	virtual void onGamePlaying() = 0;

	/**
	* When game is over, this method will be called
	*/
	virtual void onGameEnd() = 0;
};

const int MENU_START = 10001;

class GameLayer : public Layer {
public:
	GameLayer();
	~GameLayer();

	virtual bool init();
	CREATE_FUNC(GameLayer);
	virtual void onEnter() override;

	CC_SYNTHESIZE(StatusDelegate*,delegator,Delegator);

private:
	void showStartButton();
	void menuStartCallback(Ref* pSender);
	void createSquares();
	void moveFinished(Ref* pSender);


private:
	Sprite* square;
	Size visibleSize;
	Point origin;

	GameStatus gameStatus;


};





#endif /* GAMELAYER_H_ */
