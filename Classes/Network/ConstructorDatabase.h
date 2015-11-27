#pragma once

#include "NetworkObjectConstructor.h"
#include "Engine/Types.h"
#include <unordered_map>

#define RegisterConstructor(ClassName, Constructor) \
	 auto c = new ClassName(); \
	 ConstructorDatabase::get()->registerRep()

#define REGISTER_CONSTRUCTOR(T) \
	mog::network::NetworkObjectConstructor* c = new mog::network::NetworkObjectConstructorT<T>(); \
	bool isRegistered_##T = mog::network::ConstructorDatabase::get()->registerConstrcutor(c); \

namespace mog
{
	namespace network
	{
		class ConstructorDatabase
		{
		public:
			static ConstructorDatabase *get();
			bool registerConstrcutor(NetworkObjectConstructor *c);

		private:
			ConstructorDatabase();
			~ConstructorDatabase();
		private:
			static ConstructorDatabase *database;

			std::unordered_map<ID, NetworkObjectConstructor*> reps;
		};
	}
}
