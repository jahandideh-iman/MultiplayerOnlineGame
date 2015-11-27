#include "Join.h"
#include "cocos2d.h"
#include "Engine/GlobalData.h"
#include "ServerGame.h"
#include "Network/InternetAddress.h"

using mog::network::Join;
using namespace mog;


network::Join::Join()
{
}


Join::~Join()
{
}

network::Buffer *Join::serialize() const
{
	auto buffer = new Buffer();
	buffer->write("Hello");
	return buffer;
}

void Join::execute(const network::Buffer &buffer, const network::InternetAddress &address) const
{
	CCLOG("join is %s", buffer.getData());
	auto server = dynamic_cast<ServerGame*> (GlobalData::game);
	std::string name = "name";

	if (server != nullptr)
		server->joinNewPlayer(new PlayerInfo(name, &address));	
}
