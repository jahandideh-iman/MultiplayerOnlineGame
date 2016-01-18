#pragma once

#define CREATE_CONSTRUCTOR(className)\
class C_##className : public mog::network::NetworkObjectConstructor \
	{ virtual mog::network::NetworkObject *create() override { return new #className(); };

namespace mog
{
	namespace network
	{
		class NetworkObject;
		class NetworkObjectConstructor
		{
		public:
			NetworkObjectConstructor();
			~NetworkObjectConstructor();

			virtual mog::network::NetworkObject *create() = 0;
		};

		template<class T> class NetworkObjectConstructorT : public NetworkObjectConstructor {

			mog::network::NetworkObject *create() override { return new T(); }
		};

	}
}