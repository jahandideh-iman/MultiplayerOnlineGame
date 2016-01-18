#pragma once

#include "Engine/Network/NetworkObjectConstructor.h"

namespace mog
{
	namespace network
	{
		class NetworkPawn;

		class NetworkPawnFactory
		{
		public:
			static NetworkPawnFactory* get();
			static void clear();

			template<class P>
			void setNetworkPawn()
			{
				constructor = new NetworkObjectConstructorT<P>();
			}

			bool isSet();

			NetworkPawn *create();

		private:
			NetworkPawnFactory();
			~NetworkPawnFactory();

			NetworkObjectConstructor *constructor = nullptr;

			static NetworkPawnFactory* factory;
		};
	}
}


