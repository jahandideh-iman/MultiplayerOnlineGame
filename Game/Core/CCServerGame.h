#pragma once

#include "Engine/Core/Level.h"

#include "Engine/Network/ServerGame.h"
#include "ui/UIEditBox/UIEditBox.h"


#include "CCGame.h"
namespace mog
{
	//WARNING: The order of inheritance is important due to order of destruction.
	//TODO: Fix that.
	class CCServerGame : public network::ServerGame, public CCGame
	{
	public:
		static cocos2d::Scene* createScene();

		virtual void update(float dt) override;

		virtual bool init();

		void startListening(cocos2d::Ref* pSender);

		CREATE_FUNC(CCServerGame);

	protected:
		void onPawnCreated(network::NetworkPawn *p) override;

	private:
		cocos2d::MenuItemImage *startListeningButton = nullptr;

		cocos2d::ui::EditBox *serverListenPortEditBox = nullptr;
	};
}
