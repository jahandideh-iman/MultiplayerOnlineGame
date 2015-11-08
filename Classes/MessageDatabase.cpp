#include "MessageDatabase.h"
#include "Message.h"
#include "Join.h"

MessageDatabase *MessageDatabase::db = nullptr;


class EmptyMessage : public Message
{
public:
	virtual void execute(const NetworkData &data)const override{}
	virtual NetworkData *write() const override { return nullptr; }
	virtual unsigned getCode() const override  { return 0; }
};

MessageDatabase::MessageDatabase()
{
	auto j = new Join();
	map.emplace(j->getCode(), j);
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

const Message *MessageDatabase::find(unsigned messageId)
{
	auto res = map.find(messageId);
	if (res == map.end())
		return new EmptyMessage();
	return res->second;
}
