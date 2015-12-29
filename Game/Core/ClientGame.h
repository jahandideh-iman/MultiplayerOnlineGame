#pragma once

#include "Engine/Core/Game.h"
#include "Engine/Network/ClientGame.h"
#include "cocos2d.h"

class GameSocket;

namespace mog
{
	class ClientGame : public network::ClientGame , public cocos2d::Layer
	{
	public:
		static cocos2d::Scene* createScene();

		virtual void update(float dt) override;

		virtual bool init();

		void menuCloseCallback(cocos2d::Ref* pSender);


		CREATE_FUNC(ClientGame);

	private:
		void joinServer(Ref* pSender);

	private:
		GameSocket *socket = nullptr;
	};

}