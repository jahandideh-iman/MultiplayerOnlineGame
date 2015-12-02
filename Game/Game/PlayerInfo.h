#pragma once

#include "Network/InternetAddress.h"
#include <string>
namespace mog
{
	struct PlayerInfo
	{
	public:
		PlayerInfo(std::string &name, const network::InternetAddress *address);
		~PlayerInfo();

		std::string name;
		const network::InternetAddress *address;
	};
}
