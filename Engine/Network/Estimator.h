#pragma once

#include "Engine/Core/Replicable.h"

namespace mog
{
	namespace network
	{
		class Estimator
		{
		public:
			Estimator();
			virtual ~Estimator();

			virtual void update() = 0;

			void setVar(Replicable *var);

			virtual void read(const Buffer *buffer, float time) = 0;
			void setCurrentTime(float time);

		protected:
			Replicable *var = nullptr;
			float time;
		};

	}
}
