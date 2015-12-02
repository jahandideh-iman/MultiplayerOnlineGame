#pragma once

#include "Engine/Component.h"
#include <unordered_map>
#include "Engine/Serializable.h"
#include "Engine/ParameterContainer.h"

namespace mog
{

	class NetworkComponent : public Component
	{
	public:
		NetworkComponent(ID id, const GameObject *owner);
		~NetworkComponent();


		void addVariable(const std::string &name, Serializable *var);

		void addSelfToGame(Game *g);

		void networkUpdate(float dt);

		void writeReplications(Buffer *buffer) const;
		void readReplications(const Buffer *buffer);

		unsigned getIndex() const;
		void setIndex(unsigned i);

	private:
		
		unsigned index;
		std::unordered_map<std::string, Serializable*> replicationVars;
	};
}
