#include "ConstructorDatabase.h"
#include "Networkable.h"

mog::network::ConstructorDatabase * mog::network::ConstructorDatabase::database = nullptr;

mog::network::ConstructorDatabase::ConstructorDatabase()
{
}


mog::network::ConstructorDatabase::~ConstructorDatabase()
{
	for (auto c : reps)
		delete c.second;
}

bool mog::network::ConstructorDatabase::registerConstrcutor(NetworkObjectConstructor *c)
{
	Networkable *o = c->create();
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

mog::network::Networkable * mog::network::ConstructorDatabase::create(ID typeId) const
{
	return reps.find(typeId)->second->create();
}

void mog::network::ConstructorDatabase::clear()
{
	delete database;
	database = nullptr;
}


