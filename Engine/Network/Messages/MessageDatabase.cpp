#include "MessageDatabase.h"
#include "Engine/Network/Messages/Message.h"
#include "Engine/Core/Types.h"


mog::network::MessageDatabase *mog::network::MessageDatabase::db = nullptr;

namespace mog
{
	namespace network
	{
		class EmptyMessage : public Message
		{
		public:
			virtual void executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override {}
			virtual void executeOnServer(ServerGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const override {}

			AUTOID(EmptyMessage, getID)
		protected:
			virtual void fillData(ParameterContainer &parameters) const override{};
		};
	}

}

mog::network::MessageDatabase::MessageDatabase()
{
	emptyMessage = new EmptyMessage();
}

mog::network::MessageDatabase::~MessageDatabase()
{
	for (auto m : map)
		delete m.second;

	delete emptyMessage;
}

mog::network::MessageDatabase * mog::network::MessageDatabase::get()
{
	if (db == nullptr)
		db = new MessageDatabase();
	return db;
}

const mog::network::Message *mog::network::MessageDatabase::find(mog::ID messageId)
{
	auto res = map.find(messageId);
	if (res == map.end())
		return emptyMessage;
	return res->second;
}

void mog::network::MessageDatabase::registerMessage(Message *m)
{
	map.emplace(m->getID(), m);
}

void mog::network::MessageDatabase::clear()
{

	delete db;
	db = nullptr;
}
