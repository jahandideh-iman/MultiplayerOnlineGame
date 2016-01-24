#pragma once

#include "Engine/Network/Estimator.h"
#include "Engine/Core/Replicable.h"

#include <string>

namespace mog
{
	namespace network
	{
		class Extrapolator : public Estimator
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
			Extrapolator(Replicable *var);
			Extrapolator();
			~Extrapolator();

			void read(const Buffer *buffer, float time) override;

			void update() override;

		private:
			Pair point1;
			Pair point2;

		};
	}
}
