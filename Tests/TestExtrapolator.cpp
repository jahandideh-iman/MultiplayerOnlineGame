#include "CppUTest/TestHarness.h"
#include "Engine/Network/NetworkComponent.h"

#include "Engine/Network/Extrapolator.h"

#include <string>

namespace mog
{
	namespace network
	{
		//class Extrapolator : public Serializable
		//{
		//	struct Pair
		//	{
		//		Pair()
		//		{

		//		}

		//		Pair(float time, std::string data)
		//		{

		//		}

		//		float time; 
		//		std::string data = "";
		//	};
		//public:
		//	Interpolator(Replicable *var)
		//	{
		//	}

		//	void update(float dt)
		//	{
		//		float lastTime = currentTime;
		//	}

		//	void setUpdateStartTime(float t)
		//	{
		//		currentTime = t;
		//	}

		//	void readReplications(const Buffer *buffer, float time)
		//	{
		//		p2.time = p1.time;
		//		p2.data = p1.data;

		//		char * data = buffer->getData();

		//		p1.time = time;
		//		p1.data = data;

		//		delete[]data;
		//	}

		//private:
		//	Pair p1;
		//	Pair p2;

		//	float currentTime;
		//};


		TEST_GROUP(Extrapolator)
		{

		};

		TEST(Extrapolator, ExtrapolatesFloatCorrectly)
		{
			Float var = 1;
			Extrapolator extrapolator(&var);

			Buffer buffer;
			var.write(&buffer);


			extrapolator.read(&buffer, 0.0);

			buffer.clear();
			Float tempVar = 2;
			tempVar.write(&buffer);

			extrapolator.read(&buffer, 1.0);

			extrapolator.setCurrentTime(1.5);
			extrapolator.update();

			CHECK_EQUAL(2.5, var.getValue());
		}

		TEST(Extrapolator, ExtrapolatesPointCorrectly)
		{
			ReplicablePoint var(1,1);
			Extrapolator extrapolator(&var);

			Buffer buffer;
			var.write(&buffer);


			extrapolator.read(&buffer, 0.0);

			buffer.clear();
			ReplicablePoint tempVar(2,5);
			tempVar.write(&buffer);

			extrapolator.read(&buffer, 1.0);

			extrapolator.setCurrentTime(1.5);
			extrapolator.update();

			CHECK_EQUAL(2.5, var.getX());
			CHECK_EQUAL(7, var.getY());
		}
	}
}