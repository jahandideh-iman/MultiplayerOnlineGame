#pragma once

#include "NetworkObjectConstructor.h"
#include "Engine/Core/Types.h"

#include <unordered_map>

#define RegisterConstructor(ClassName, Constructor) \
	 auto c = new ClassName(); \
	 ConstructorDatabase::get()->registerRep()

#define REGISTER_CONSTRUCTOR(T) \
	mog::network::NetworkObjectConstructor* c_##T = new mog::network::NetworkObjectConstructorT<T>(); \
	bool isRegistered_##T = mog::network::ConstructorDatabase::get()->registerConstrcutor(c_##T); \

namespace mog
{
	namespace network
	{
		class ConstructorDatabase
		{
		public:
			static ConstructorDatabase *get();
			static void clear();

			bool registerConstrcutor(NetworkObjectConstructor *c);

			NetworkObject *create(ID typeId) const;

		private:
			ConstructorDatabase();
			~ConstructorDatabase();
		private:
			static ConstructorDatabase *database;

			std::unordered_map<ID, NetworkObjectConstructor*> reps;
		};
	}
}
