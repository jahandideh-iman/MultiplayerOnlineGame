#pragma once

#include "cocos2d.h"

class GameSocket;

class ServerGame : public cocos2d::Layer
{
public:

	~ServerGame();

	static cocos2d::Scene* createScene();

	virtual void update(float dt) override;

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);


	CREATE_FUNC(ServerGame);

private:
};

