#pragma once

#include "CppUTest/TestHarness.h"
#include "Engine/Network/NetworkManager.h"

#include "Engine/Network/ClientGame.h"
#include "Engine/Network/ServerGame.h"
#include "Engine/Network/Messages/MessageDatabase.h"

#include "MockSocketDataBase.h"
#include "MockSocket.h"

namespace mog
{
	namespace network
	{
		class NetworkBase : public Utest
		{
		protected:
			MockSocketDataBase db;

			ServerGame *serverGame;
			ClientGame *clientGame;

			NetworkManager *serverManager;
			NetworkManager *clientManager;

			unsigned clientPort = 8082;
			unsigned serverPort = 8081;

			void setup() override
			{
				serverGame = new ServerGame();
				clientGame = new ClientGame();

				serverManager = serverGame->getNetworkManager();
				clientManager = clientGame->getNetworkManager();

				serverManager->setSocket(new MockSocket(&db));
				clientManager->setSocket(new MockSocket(&db));

				serverManager->setPort(serverPort);
				clientManager->setPort(clientPort);
			}

			void teardown() override
			{
				delete serverGame;
				delete clientGame;

				MessageDatabase::clear();
			}
		};
	}
}