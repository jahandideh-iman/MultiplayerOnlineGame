#pragma once

#include "Engine/Core/Level.h"

#include "Engine/Network/ServerGame.h"
#include "ui/UIEditBox/UIEditBox.h"
#include "Engine/Network/NetworkPawn.h"


#include "CCGame.h"
namespace mog
{
	class CCServerGame :  public CCGame
	{
		class CustomServerGame : public network::ServerGame, public CCNetworkGame
		{
		public:
			CustomServerGame(CCServerGame *game) : CCNetworkGame(game)
			{
			}
			void onPawnCreated(network::NetworkPawn *p) override
			{
				p->setPosition(Point(50, 50));
			}
		};

	public:
		static cocos2d::Scene* createScene();

		~CCServerGame();

		virtual void update(float dt) override;

		virtual bool init();

		void startListening(cocos2d::Ref* pSender);

		CREATE_FUNC(CCServerGame);

	protected:
		

	private:
		cocos2d::MenuItemImage *startListeningButton = nullptr;

		cocos2d::ui::EditBox *serverListenPortEditBox = nullptr;

		CustomServerGame *serverGame;
	};
}
