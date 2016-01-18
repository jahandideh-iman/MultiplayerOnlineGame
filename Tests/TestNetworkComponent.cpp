#include "CppUTest/TestHarness.h"

#include "Engine/Network/NetworkComponent.h"
#include "Engine/Core/ParameterContainer.h"
#include "Engine/Core/Types.h"

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
	}
}