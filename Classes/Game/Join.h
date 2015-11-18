#pragma once
#include "Network/Command.h"
namespace mog
{
	namespace network
	{
		class Join :
			public Command
		{
		public:
			Join();
			~Join();

			virtual void execute(const NetworkData &data, const InternetAddress& address) const override;

			virtual NetworkData *write() const override;

			virtual unsigned getCode() const override;
		};
	}
}
