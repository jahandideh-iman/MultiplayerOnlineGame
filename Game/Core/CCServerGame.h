#pragma once

#include "Engine/Core/Level.h"

#include "Engine/Network/ServerGame.h"

#include "CCGame.h"
namespace mog
{
	class CCServerGame : public network::ServerGame , public CCGame
	{
	public:

		~CCServerGame();

		static cocos2d::Scene* createScene(unsigned portNumber);

		virtual void update(float dt) override;

		virtual bool init(unsigned portNumber);

		void setPortNumber(unsigned port);

		void menuCloseCallback(cocos2d::Ref* pSender);

		static CCServerGame *create(unsigned portNumber);

	protected:
		void onPawnCreated(network::NetworkPawn *p) override;

	private:
		unsigned portNumber = 1000;
	};
}
