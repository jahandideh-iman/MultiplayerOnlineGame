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

			virtual void execute(const Buffer &data, const network::InternetAddress &address) const;
			virtual Buffer *serialize() const;

			AUTOID(LoadLevel, getID)

		private:
			char *levelName = nullptr;
		};
	}
}