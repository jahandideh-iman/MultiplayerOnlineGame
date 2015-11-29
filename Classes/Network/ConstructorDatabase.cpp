#include "ConstructorDatabase.h"
#include "NetworkObject.h"

mog::network::ConstructorDatabase * mog::network::ConstructorDatabase::database = nullptr;

mog::network::ConstructorDatabase::ConstructorDatabase()
{
}


mog::network::ConstructorDatabase::~ConstructorDatabase()
{
}

bool mog::network::ConstructorDatabase::registerConstrcutor(NetworkObjectConstructor *c)
{
	NetworkObject *o = c->create();
	reps.emplace(o->getNetworkID(), c);
	delete o;
	return true;
}

mog::network::ConstructorDatabase * mog::network::ConstructorDatabase::get()
{
	if (database == nullptr)
		database = new ConstructorDatabase();
	return database;
}

mog::network::NetworkObject * mog::network::ConstructorDatabase::create(ID typeId) const
{
	return reps.find(typeId)->second->create();
}


