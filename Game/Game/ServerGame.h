#pragma once

#include "PlayerInfo.h"
#include "Engine/Game.h"
#include "Engine/Level.h"
#include "cocos2d.h"

namespace mog
{
	class ServerGame : public Game , public cocos2d::Layer 
	{
	public:

		~ServerGame();

		static cocos2d::Scene* createScene();

		virtual void update(float dt) override;

		virtual bool init();

		void menuCloseCallback(cocos2d::Ref* pSender);

		CREATE_FUNC(ServerGame);

		void joinNewPlayer(PlayerInfo *info);


	private:

		std::vector<PlayerInfo*> playersInfo;
	};
}
