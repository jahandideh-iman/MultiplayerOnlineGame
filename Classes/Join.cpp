#include "Join.h"
#include "cocos2d.h"

Join::Join()
{
}


Join::~Join()
{
}

NetworkData *Join::write() const
{

	auto data = new char[20];
	auto s = sprintf(data, "%u", this->getCode());
	strcpy(&data[s+1], "Hello");

	NetworkData *nd = new NetworkData(data, s+1+6);
	return nd;
}

void Join::execute(const NetworkData &data) const
{
	CCLOG("join is %s",data.data);
}

unsigned Join::getCode() const
{
	return 1000;
}
