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
			ClientGame *clientGame1;
			ClientGame *clientGame2;

			NetworkManager *serverManager;
			NetworkManager *clientManager1;
			NetworkManager *clientManager2;

			unsigned serverPort = 8081;
			unsigned clientPort1 = 8082;
			unsigned clientPort2 = 8083;


			void setup() override
			{
				serverGame = new ServerGame();
				clientGame1 = new ClientGame();
				clientGame2 = new ClientGame();

				serverManager = serverGame->getNetworkManager();
				clientManager1 = clientGame1->getNetworkManager();
				clientManager2 = clientGame2->getNetworkManager();

				serverManager->setSocket(new MockSocket(&db));
				clientManager1->setSocket(new MockSocket(&db));
				clientManager2->setSocket(new MockSocket(&db));

				serverManager->setPort(serverPort);
				clientManager1->setPort(clientPort1);
				clientManager2->setPort(clientPort2);
			}

			void teardown() override
			{
				delete serverGame;
				delete clientGame1;
				delete clientGame2;

				MessageDatabase::clear();
			}
		};
	}
}