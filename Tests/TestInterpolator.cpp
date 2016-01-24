#include "CppUTest/TestHarness.h"
#include "Engine/Network/NetworkComponent.h"

#include <string>

namespace mog
{
	namespace network
	{
		class Interpolator
		{
			struct Pair
			{
				Pair()
				{

				}

				Pair(float time, std::string data)
				{

				}

				float time; 
				std::string data = "";
			};
		public:
			Interpolator(NetworkComponent *comp)
			{

			}

			void update(float dt)
			{
				float lastTime = currentTime;
			}

			void setUpdateStartTime(float t)
			{
				currentTime = t;
			}

			void readReplications(const Buffer *buffer, float time)
			{
				p2.time = p1.time;
				p2.data = p1.data;

				char * data = buffer->getData();

				p1.time = time;
				p1.data = data;

				delete[]data;
			}

		private:
			Pair p1;
			Pair p2;

			float currentTime;
		};

		TEST_GROUP(Interpolator)
		{

		};

		//TEST(Interpolator, d)
		//{
		//	NetworkComponent netComp1("", nullptr);
		//	NetworkComponent netComp2("", nullptr);
		//	Integer var1 = 1;
		//	Integer var2 = var1;

		//	netComp1.addVariable("var", &var1);
		//	netComp2.addVariable("var", &var2);

		//	Interpolator interpolator(&netComp1);

		//	Buffer buffer;

		//	netComp2.writeReplications(&buffer);

		//	interpolator.readReplications(&buffer,0);

		//	var2.setValue(2);
		//	buffer.clear();
		//	netComp2.writeReplications(&buffer);

		//	interpolator.readReplications(&buffer,1);
		//	interpolator.setUpdateStartTime(0);
		//	interpolator.update(0.5);

		//	CHECK_EQUAL(1.5, var1.getValue());
		//}
	}
}