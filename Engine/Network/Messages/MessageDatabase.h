#pragma once

#include "Engine/Types.h"
#include <unordered_map>

#define REGISTER_MESSAGE(T) \
	mog::network::Message* m = new T(); \
	mog::network::MessageDatabase::get()->registerMessage(m); \

namespace mog
{
	namespace network
	{
		class Message;

		class MessageDatabase
		{
		public:

			static MessageDatabase *get();
			static void clear();

			const Message *find(ID messageId);

			void registerMessage(Message *m);
		private:
			MessageDatabase();
			~MessageDatabase();

		private:
			static MessageDatabase *db;

			std::unordered_map<ID, Message *> map;

		};
	}

}