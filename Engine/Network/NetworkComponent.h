#pragma once

#include "Engine/Core/Component.h"
#include "Engine/Core/Serializable.h"
#include "Engine/Core/ParameterContainer.h"

#include <unordered_map>

namespace mog
{
	namespace network
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
}
