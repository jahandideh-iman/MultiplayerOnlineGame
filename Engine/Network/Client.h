#pragma once

#include "Engine/Network/InternetAddress.h"
#include <string>
namespace mog
{
	namespace network
	{
		class Client
		{
		public:
			Client(std::string name, const network::InternetAddress *address);
			Client(const Client *other);

			~Client();

			bool operator== (const Client &other) const;
			bool operator!= (const Client &other) const;

			std::string name;
			const network::InternetAddress *address;
		};
	}
}
