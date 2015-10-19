#pragma once

#include "cocos2d.h"

class ClientGame : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual void update(float dt) override;

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	void updateNetwork();

	CREATE_FUNC(ClientGame);
};

