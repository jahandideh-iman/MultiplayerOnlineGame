#pragma once

#include "Engine/Core/Level.h"
#include "cocos2d.h"
#include "Engine/Network/ServerGame.h"

namespace mog
{
	class ServerGame : public network::ServerGame , public cocos2d::Layer 
	{
	public:

		~ServerGame();

		static cocos2d::Scene* createScene();

		virtual void update(float dt) override;

		virtual bool init();

		void menuCloseCallback(cocos2d::Ref* pSender);

		CREATE_FUNC(ServerGame);
	};
}
