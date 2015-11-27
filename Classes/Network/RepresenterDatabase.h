#pragma once

#include "GameObjectRepresenter.h"
#include <unordered_map>

namespace mog
{
	namespace network
	{
		class RepresenterDatabase
		{
		public:
			RepresenterDatabase *get();
			void registerRep(const std::string &name,GameObjectRepresenter *rep);

		private:
			RepresenterDatabase();
			~RepresenterDatabase();
		private:
			static RepresenterDatabase *database;

			std::unordered_map<std::string, GameObjectRepresenter*> reps;
		};
	}
}
