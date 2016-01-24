#pragma once

#define CREATE_CONSTRUCTOR(className)\
class C_##className : public mog::network::NetworkObjectConstructor \
	{ virtual mog::network::NetworkObject *create() override { return new #className(); };

namespace mog
{
	namespace network
	{
		class Networkable;
		class NetworkObjectConstructor
		{
		public:
			NetworkObjectConstructor();
			~NetworkObjectConstructor();

			virtual mog::network::Networkable *create() = 0;
		};

		template<class T> class NetworkObjectConstructorT : public NetworkObjectConstructor {

			mog::network::Networkable *create() override { return new T(); }
		};

	}
}