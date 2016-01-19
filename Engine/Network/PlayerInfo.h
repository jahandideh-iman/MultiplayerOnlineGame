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
			PlayerInfo(std::string name, const network::InternetAddress *address);
			~PlayerInfo();

			bool operator== (const PlayerInfo &other) const;
			bool operator!= (const PlayerInfo &other) const;

			std::string name;
			const network::InternetAddress *address;
		};
	}
}
