#include "CppUTest/TestHarness.h"
#include "Engine/Core/Buffer.h"
#include "NetworkBase.h"

#include "Engine/Network/ConstructorDatabase.h"
#include "Engine/Network/NetworkPawnFactory.h"

#include "Engine/Network/Messages/JoinMessage.h"
#include "Engine/Network/Messages/LeaveMessage.h"

#include "Engine/Network/NetworkPawn.h"
#include "Engine/Core/LevelFactory.h"

namespace mog
{
	namespace network
	{
		TEST_GROUP_BASE(LeaveMessage, NetworkBase)
		{
			void teardown() override
			{
				NetworkBase::teardown();
				NetworkPawnFactory::clear();
				LevelFactory::clear();
			}
			bool hasPawn(NetworkManager *manager)
			{
				for (auto o : manager->getNetworkGameObjects())
				{
					if (dynamic_cast<const NetworkPawn*> (o) != nullptr)
						return true;
				}

				return false;
			}
		};

		TEST(LeaveMessage, PlayerInfoIsRemoveFromServerGameAndServerManager)
		{
			REGISTER_MESSAGE(JoinMessage);
			REGISTER_MESSAGE(LeaveMessage);

			clientManager1->sendMessage(JoinMessage("player"), serverAddress);
			serverManager->update();

			clientManager1->sendMessage(LeaveMessage("player"), serverAddress);
			serverManager->update();

			CHECK_FALSE(serverGame->hasClient(&Client("player", new InternetAddress(clientAddress1))));
			CHECK_FALSE(serverManager->hasClient(&clientAddress1));
		}
	}
}