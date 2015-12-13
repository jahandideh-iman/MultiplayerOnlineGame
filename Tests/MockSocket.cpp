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
	db->find(destination.getPort())->buffer.write(data);
	return true;
}

int mog::network::MockSocket::receive(Address &sender, void * data, int size)
{
	char *newData = buffer.getData();
	strcpy_s((char*)data, size, newData);

	delete[]newData;
	return buffer.getSize();
	buffer.clear();
}
