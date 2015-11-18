#pragma once

#include "Network/InternetAddress.h"
#include <string>
namespace mog
{
	class PlayerInfo
	{
	public:
		PlayerInfo(std::string &name, const network::InternetAddress *address);
		~PlayerInfo();

	private:
		std::string name;
		const network::InternetAddress *address;
	};
}
