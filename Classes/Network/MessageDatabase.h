#pragma once

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

			const Message * find(unsigned messageId);
		private:
			MessageDatabase();
			~MessageDatabase();

		private:
			static MessageDatabase *db;

			std::unordered_map<unsigned, Message *> map;

		};
	}

}