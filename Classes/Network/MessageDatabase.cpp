#include "MessageDatabase.h"
#include "Message.h"
#include "Game/Join.h"
#include "LoadLevel.h"
#include "Engine/Types.h"



using namespace mog::network;

MessageDatabase *MessageDatabase::db = nullptr;

namespace mog
{
	class EmptyMessage : public Message
	{
	public:
		virtual void execute(const ParameterContainer &parameters, const InternetAddress &address)const override{}
		
		AUTOID(EmptyMessage, getID)
	protected:
		virtual void fillData(ParameterContainer *parameters) const override{};
	};
}

MessageDatabase::MessageDatabase()
{
	auto j = new Join();
	map.emplace(j->getID(), j);
	auto k = new LoadLevel();
	map.emplace(k->getID(), k);
}


MessageDatabase::~MessageDatabase()
{
}

MessageDatabase * MessageDatabase::get()
{
	if (db == nullptr)
		db = new MessageDatabase();
	return db;
}

const Message *MessageDatabase::find(mog::ID messageId)
{
	auto res = map.find(messageId);
	if (res == map.end())
		return new EmptyMessage();
	return res->second;
}
