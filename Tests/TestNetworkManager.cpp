#include "CppUTest/TestHarness.h"

#include "Engine/Network/NetworkManager.h"



namespace mog
{
	namespace network
	{
		class MockNetworkMaager : public NetworkManager
		{
		public:
			MockNetworkMaager() : NetworkManager(nullptr)
			{

			}

			void processUpdate() override
			{
				numberOfUpdatesCalled++;
			}

			unsigned numberOfUpdatesCalled = 0;
		};
		TEST_GROUP(NetworkManager)
		{

		};

		TEST(NetworkManager, DoesNotUpdateIfElapsedTimeIsLessThanFrameTime)
		{
			MockNetworkMaager manager;

			manager.setUpdateRate(15);

			manager.update(1.0 / 15 - EPSILON);

			CHECK_EQUAL(0, manager.numberOfUpdatesCalled);
		}

		TEST(NetworkManager, UpdatesIfElapsedTimeIsNotLessThanFrameTime)
		{
			MockNetworkMaager manager;

			manager.setUpdateRate(15);

			manager.update(1.0 / 15 + EPSILON);

			CHECK_EQUAL(1, manager.numberOfUpdatesCalled);
		}

		TEST(NetworkManager, AddsToElapsedTimeByEachUpdate)
		{
			MockNetworkMaager manager;

			manager.setUpdateRate(15);

			manager.update(1.0 / 30 - EPSILON);
			manager.update(1.0 / 30 - EPSILON);

			CHECK_EQUAL(0, manager.numberOfUpdatesCalled);

			manager.update(3 * EPSILON);
			CHECK_EQUAL(1, manager.numberOfUpdatesCalled);
		}
	}
}