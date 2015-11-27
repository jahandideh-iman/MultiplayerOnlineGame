#include "RepresenterDatabase.h"


mog::network::RepresenterDatabase::RepresenterDatabase()
{
}


mog::network::RepresenterDatabase::~RepresenterDatabase()
{
}

void mog::network::RepresenterDatabase::registerRep(const std::string &name, GameObjectRepresenter *rep)
{
	reps.emplace(name, rep);
}
