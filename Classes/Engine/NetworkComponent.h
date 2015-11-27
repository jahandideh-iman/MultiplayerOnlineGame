#pragma once

#include "Component.h"
#include <unordered_map>

namespace mog
{
	class NetworkComponent : public Component
	{
	public:
		NetworkComponent();
		~NetworkComponent();

		void addRepVar(const std::string &name, int *address);

	private:
		std::unordered_map<std::string, int*> replicationVars;
	};
}
