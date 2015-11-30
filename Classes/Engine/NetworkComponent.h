#pragma once

#include "Component.h"
#include <unordered_map>
#include "Engine/Serializable.h"

namespace mog
{

	class NetworkComponent : public Component
	{
	public:
		NetworkComponent(ID id, const GameObject *owner);
		~NetworkComponent();


		void addVariable(const std::string &name, Serializable *var);

		void addSelfToGame(Game *g){};

	private:
		std::unordered_map<std::string, Serializable*> replicationVars;
	};
}
