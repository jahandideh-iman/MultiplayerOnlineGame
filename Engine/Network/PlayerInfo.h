#pragma once

#include "Engine/Network/InternetAddress.h"
#include <string>
namespace mog
{
	namespace network
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
}
