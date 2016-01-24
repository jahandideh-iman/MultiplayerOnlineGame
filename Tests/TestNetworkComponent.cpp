#include "CppUTest/TestHarness.h"

#include "Engine/Core/Game.h"
#include "Engine/Network/NetworkComponent.h"
#include "Engine/Core/ParameterContainer.h"
#include "Engine/Network/Extrapolator.h"
#include "Engine/Core/Types.h"
#include "MockNetworkGameObject.h"

namespace mog
{
	namespace network
	{
		TEST_GROUP(NetworkComponent)
		{

		};

		TEST(NetworkComponent, HasTheAddedVariable)
		{
			NetworkComponent networkComponent("",nullptr);
			Integer var;

			networkComponent.addVariable("var", &var);

			CHECK_TRUE(networkComponent.hasVarialbe("var"));
		}

		TEST(NetworkComponent, DoesNotHaveTheRemovedVariable)
		{
			NetworkComponent networkComponent("", nullptr);
			Integer var;

			networkComponent.addVariable("var", &var);
			networkComponent.removeVariable("var");

			CHECK_FALSE(networkComponent.hasVarialbe("var"));
		}

		TEST(NetworkComponent, CorrectlyWritesReplications)
		{
			NetworkComponent networkComponent("", nullptr);
			Integer var1 = 1;
			Integer var2 = 2;
			networkComponent.addVariable("var1", &var1);
			networkComponent.addVariable("var2", &var2);

			Buffer buffer;

			networkComponent.writeReplications(&buffer);

			ParameterContainer c(&buffer);

			CHECK_EQUAL(var1.getValue(), atoi(c.get("var1").c_str()));
			CHECK_EQUAL(var2.getValue(), atoi(c.get("var2").c_str()));
		}

		TEST(NetworkComponent, CorrectlyReadsReplications)
		{
			NetworkComponent networkComponent1("", nullptr);
			NetworkComponent networkComponent2("", nullptr);
			Integer comp1var = 1;
			Integer comp2var = 2;

			networkComponent1.addVariable("var", &comp1var);
			networkComponent2.addVariable("var", &comp2var);

			Buffer buffer;
			networkComponent1.writeReplications(&buffer);

			networkComponent2.readReplications(&buffer);

			CHECK_EQUAL(comp1var.getValue(), comp2var.getValue());
		}

		TEST(NetworkComponent, IsDirtyIfAtLeastOnVariableIsDirty)
		{
			NetworkComponent networkComponent("", nullptr);
			Integer var1 = 1;
			Integer var2 = 2;
			networkComponent.addVariable("var1", &var1);
			networkComponent.addVariable("var2", &var2);

			var1.setDirty(true);
			var2.setDirty(false);

			CHECK_TRUE(networkComponent.isDirty());
		}

		TEST(NetworkComponent, IsNotDirtyIfAllVariableAreNotDirty)
		{
			NetworkComponent networkComponent("", nullptr);
			Integer var1 = 1;
			Integer var2 = 2;
			networkComponent.addVariable("var1", &var1);
			networkComponent.addVariable("var2", &var2);

			var1.setDirty(false);
			var2.setDirty(false);

			CHECK_FALSE(networkComponent.isDirty());
		}

		TEST(NetworkComponent, CorrectlyWritesDirtyReplications)
		{
			NetworkComponent networkComponent("", nullptr);
			Integer var1 = 1;
			Integer var2 = 2;
			networkComponent.addVariable("var1", &var1);
			networkComponent.addVariable("var2", &var2);

			var1.setDirty(false);
			var2.setDirty(true);

			Buffer buffer;

			networkComponent.writeReplications(&buffer, true);

			ParameterContainer c(&buffer);

			CHECK_FALSE(c.has("var1"));
			CHECK_TRUE(c.has("var2"));
		}

		TEST(NetworkComponent, SetDirtyDelegatesToVariables)
		{
			NetworkComponent networkComponent1("", nullptr);
			NetworkComponent networkComponent2("", nullptr);
			Integer comp1var = 1;
			Integer comp2var = 2;

			networkComponent1.addVariable("var", &comp1var);
			networkComponent2.addVariable("var", &comp2var);

			comp1var.setDirty(true);
			networkComponent1.setDirty(false);

			comp2var.setDirty(false);
			networkComponent2.setDirty(true);

			CHECK_FALSE(comp1var.isDirty());
			CHECK_TRUE(comp2var.isDirty());
		}

		TEST(NetworkComponent, IntergratesExtrapolator)
		{
			Game game;
			auto networkObject = new MockNetworkGameObject();
	
			auto networkComponent1 = new NetworkComponent("net1", networkObject);
			auto networkComponent2 = new NetworkComponent("net2", networkObject);

			networkObject->addComponent(networkComponent1);
			networkObject->addComponent(networkComponent2);
			game.addGameObject(networkObject);

			Float comp1var = 1;
			Float comp2var;

			Buffer buffer;

			networkComponent1->addVariable("var", &comp1var);
			networkComponent2->addVariable("var", &comp2var);

			auto extrapolator = new Extrapolator();

			networkComponent1->addEstimator("var", extrapolator);


			comp2var = 1;
			networkComponent2->writeReplications(&buffer);
						
			game.update(1); // time = 1
			networkComponent1->readReplications(&buffer);

			buffer.clear();
			comp2var = 2;
			networkComponent2->writeReplications(&buffer);

			game.update(1); // time = 2
			networkComponent1->readReplications(&buffer);

			game.update(0.5); // time = 2.5
			
			CHECK_EQUAL(2.5, comp1var.getValue());
		}
	}
}