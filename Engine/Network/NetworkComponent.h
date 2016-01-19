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
			void removeVariable(const std::string &name);
			void removeAllVariables();
			bool hasVarialbe(const std::string &name);

			void addSelfToGame(Game *g);

			void writeReplications(Buffer *buffer) const;
			void readReplications(const Buffer *buffer);

		private:
			std::unordered_map<std::string, Serializable*> replicationVars;
		};
	}
}
