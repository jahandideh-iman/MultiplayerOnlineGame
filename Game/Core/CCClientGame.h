#pragma once

#include "Engine/Core/Game.h"
#include "Engine/Network/ClientGame.h"
#include "ui/UIEditBox/UIEditBox.h"

#include "CCGame.h"

class GameSocket;

namespace mog
{


	class CCClientGame : public CCGame
	{

		class CustomClientGame : public network::ClientGame, public CCNetworkGame
		{
		public:
			CustomClientGame(CCClientGame *game) : CCNetworkGame(game)
			{
			}
		};

	public:
		static cocos2d::Scene* createScene();

		virtual void update(float dt) override;

		virtual bool init();

		CREATE_FUNC(CCClientGame);

	private:
		void joinServer(Ref* pSender);

	private:
		GameSocket *socket = nullptr;

		cocos2d::MenuItemImage *joinServerButton = nullptr;

		cocos2d::ui::EditBox *serverAddressEditBox = nullptr;
		cocos2d::ui::EditBox *serverPortEditBox = nullptr;

		std::string playerName = "player";

		CustomClientGame *clientGame;
	};

}