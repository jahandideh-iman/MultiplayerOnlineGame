#include "MockSocketDataBase.h"


mog::network::MockSocketDataBase::MockSocketDataBase()
{
}


mog::network::MockSocketDataBase::~MockSocketDataBase()
{
	sockets.clear();
}

void mog::network::MockSocketDataBase::add(unsigned short port, MockSocket *socket)
{
	sockets.emplace(port, socket);
}

mog::network::MockSocket * mog::network::MockSocketDataBase::find(unsigned short port)
{
	return sockets.find(port)->second;
}
