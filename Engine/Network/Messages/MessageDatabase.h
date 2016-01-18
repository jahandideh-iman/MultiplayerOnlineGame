#pragma once

#include "Engine/Core/Types.h"
#include <unordered_map>

#define REGISTER_MESSAGE(T) \
	mog::network::Message* message_##T = new T(); \
	mog::network::MessageDatabase::get()->registerMessage(message_##T); \

namespace mog
{
	namespace network
	{
		class Message;

		class EmptyMessage;

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

			EmptyMessage *emptyMessage;

		};
	}
}