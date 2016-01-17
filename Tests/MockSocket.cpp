#include "MockSocket.h"
#include "MockSocketDataBase.h"

mog::network::MockSocket::MockSocket(MockSocketDataBase *db)
{
	this->db = db;
}


mog::network::MockSocket::~MockSocket()
{
}

void mog::network::MockSocket::open(unsigned short port)
{
	this->port = port;
	db->add(port, this);
}

bool mog::network::MockSocket::send(const Address &destination, const char * data, int size)
{
	db->find(destination.getPort())->storeMessage(this->port, data);
	return true;
}

int mog::network::MockSocket::receive(Address &sender, void * data, int size)
{

	if (messages.empty())
		return 0;

	auto &firstClientMessages = messages.begin()->second;

	std::string firstMessage = *(firstClientMessages.begin());

	strcpy_s((char*)data, size, firstMessage.c_str());

	sender.setPort(messages.begin()->first);

	firstClientMessages.erase(firstClientMessages.begin());

	if (firstClientMessages.empty())
		messages.erase(messages.begin());

	return firstMessage.size() + 1;
}

void mog::network::MockSocket::storeMessage(unsigned senderPort, const char * data)
{
	messages[senderPort].push_back(data);
}
