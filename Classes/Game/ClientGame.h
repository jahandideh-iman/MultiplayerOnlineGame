#pragma once

#include "cocos2d.h"

class GameSocket;

namespace mog
{
	class ClientGame : public cocos2d::Layer
	{
	public:
		static cocos2d::Scene* createScene();

		virtual void update(float dt) override;

		virtual bool init();

		void menuCloseCallback(cocos2d::Ref* pSender);

		void updateNetwork();

		CREATE_FUNC(ClientGame);

	private:
		void joinServer(Ref* pSender);

	private:
		GameSocket *socket = nullptr;
	};

}