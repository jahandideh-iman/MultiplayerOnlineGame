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

	char *newData = messages.begin()->second.getData();
	strcpy_s((char*)data, size, newData);

	int bufferSize = messages.begin()->second.getSize();
	sender.setPort(messages.begin()->first);

	delete[]newData;
	messages.begin()->second.clear();

	messages.erase(messages.begin());

	return bufferSize;
}

void mog::network::MockSocket::storeMessage(unsigned senderPort, const char * data)
{
	messages[senderPort].write(data);
}
