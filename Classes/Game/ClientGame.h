#pragma once

#include "Engine/Game.h"

class GameSocket;

namespace mog
{
	class ClientGame : public Game
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