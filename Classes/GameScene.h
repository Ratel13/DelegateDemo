/*
 * GameScene.h
 *
 *  Created on: 2014年7月29日
 *      Author: tubuntu
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_
#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Scene {
public:
	GameScene();
	~GameScene();

	virtual bool init();
	CREATE_FUNC(GameScene);
};




#endif /* GAMESCENE_H_ */
