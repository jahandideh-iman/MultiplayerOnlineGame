#include "LevelDatabase.h"
#include "Engine/Core/Level.h"




mog::LevelDatabase *mog::LevelDatabase::db = nullptr;

//namespace mog
//{
//	class EmptyMessage : public Message
//	{
//	public:
//		virtual void executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override {}
//		virtual void executeOnServer(ServerGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override {}
//
//		AUTOID(EmptyMessage, getID)
//	protected:
//		virtual void fillData(ParameterContainer &parameters) const override{};
//	};
//
//}

mog::LevelDatabase::LevelDatabase()
{
}

mog::LevelDatabase::~LevelDatabase()
{
	for (auto m : map)
		delete m.second;
}

mog::LevelDatabase * mog::LevelDatabase::get()
{
	if (db == nullptr)
		db = new LevelDatabase();
	return db;
}

mog::Level *mog::LevelDatabase::find(mog::ID messageId)
{
	auto res = map.find(messageId);
	if (res == map.end())
		return nullptr; //TODO: Change nullptr to empty level
	return res->second;
}

void mog::LevelDatabase::registerLevel(Level *l)
{
	map.emplace(l->getID(), l);
}

void mog::LevelDatabase::clear()
{
	delete db;
	db = nullptr;
}
