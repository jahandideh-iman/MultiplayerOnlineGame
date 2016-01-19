#pragma once

#include "Engine/Core/Level.h"
#include "cocos2d.h"
#include "Engine/Network/ServerGame.h"

namespace mog
{
	class CCServerGame : public network::ServerGame , public cocos2d::Layer 
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
