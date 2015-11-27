#pragma once

#include "Message.h"

namespace mog
{
	namespace network
	{
		class LoadLevel : public Message
		{
		public:
			LoadLevel(char *name);
			LoadLevel();
			~LoadLevel();

			virtual void execute(const NetworkData &data, const network::InternetAddress &address) const;
			virtual NetworkData *write() const;
			virtual unsigned getCode() const;

		private:
			char *levelName = nullptr;
		};
	}
}