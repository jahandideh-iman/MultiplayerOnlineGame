#pragma once

#include "Engine/Types.h"
#include <unordered_map>


namespace mog
{
	namespace network
	{
		class Message;

		class MessageDatabase
		{
		public:

			static MessageDatabase *get();

			const Message * find(ID messageId);
		private:
			MessageDatabase();
			~MessageDatabase();

		private:
			static MessageDatabase *db;

			std::unordered_map<ID, Message *> map;

		};
	}

}