#pragma once

#include "Engine/Core/Game.h"
#include "Engine/Network/ClientGame.h"

#include "CCGame.h"

class GameSocket;

namespace mog
{
	class CCClientGame : public network::ClientGame , public CCGame
	{
	public:
		static cocos2d::Scene* createScene(std::string address, unsigned portNumber);

		virtual void update(float dt) override;

		virtual bool init(std::string address, unsigned portNumber);

		void menuCloseCallback(cocos2d::Ref* pSender);

		static CCClientGame *create(std::string address, unsigned portNumber);



	private:
		void joinServer(Ref* pSender);

	private:
		GameSocket *socket = nullptr;

		cocos2d::MenuItemImage *joinServerButton = nullptr;

		std::string playerName = "player";
	};

}