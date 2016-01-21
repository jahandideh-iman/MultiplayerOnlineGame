#pragma once

#include "CppUTest/TestHarness.h"
#include "Engine/Network/NetworkManager.h"

#include "Engine/Network/ClientGame.h"
#include "Engine/Network/ServerGame.h"
#include "Engine/Network/Messages/MessageDatabase.h"
#include "Engine/Network/ConstructorDatabase.h"
#include "Engine/Network/NetworkPawnFactory.h"

#include "Engine/Network/ServerNetworkManager.h"

#include "MockSocketDataBase.h"
#include "MockSocket.h"
#include "MockGameObject.h"

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

			Client *client1;
			Client *client2;

			ServerNetworkManager *serverManager;
			NetworkManager *clientManager1;
			NetworkManager *clientManager2;

			InternetAddress serverAddress;
			InternetAddress clientAddress1;
			InternetAddress clientAddress2;

			unsigned lastClientInstanceId = 0;


			void setup() override
			{
				serverGame = new ServerGame();
				clientGame1 = new ClientGame();
				clientGame2 = new ClientGame();



				serverAddress.setPort(8081);
				clientAddress1.setPort(8082);
				clientAddress2.setPort(8083);

				client1 = new Client("clinet1", new InternetAddress(clientAddress1));
				client2 = new Client("clinet1", new InternetAddress(clientAddress2));

				serverManager = dynamic_cast<ServerNetworkManager *> (serverGame->getNetworkManager());
				clientManager1 = clientGame1->getNetworkManager();
				clientManager2 = clientGame2->getNetworkManager();

				serverManager->setSocket(new MockSocket(&db));
				clientManager1->setSocket(new MockSocket(&db));
				clientManager2->setSocket(new MockSocket(&db));

				serverManager->setPort(serverPort);
				clientManager1->setPort(clientPort1);
				clientManager2->setPort(clientPort2);

				clientGame1->setServerAddress(serverAddress);
				clientGame2->setServerAddress(serverAddress);
			}

			void teardown() override
			{

				delete client1;
				delete client2;

				delete serverGame;
				delete clientGame1;
				delete clientGame2;

				MessageDatabase::clear();
				ConstructorDatabase::clear();
				NetworkPawnFactory::clear();
			}

			//NOTE: These parameters are normally set in server
			void initialClientNetworkGameObject(NetworkGameObject *obj)
			{
				obj->setInstanceId(lastClientInstanceId);
				obj->setRole(Role_Proxy);


				lastClientInstanceId++;
			}

			bool gameHasLevelObjects(Game *game, Level *level)
			{
				if (game->getGameObjects().size() < level->getGameObjects().size())
					return false;

				for (auto gameO : game->getGameObjects())
				{
					bool has = false;
					for (auto levelO : level->getGameObjects())
					{
						if (((MockGameObject*)levelO)->key == ((MockGameObject*)gameO)->key)
							has = true;
					}
					if (has == false)
						return false;
				}
				return true;
			}

		private:
			unsigned serverPort = 8081;
			unsigned clientPort1 = 8082;
			unsigned clientPort2 = 8083;
		};
	}
}