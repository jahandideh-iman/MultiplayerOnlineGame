#pragma once

#include "Engine/Core/Component.h"
#include "Engine/Core/Replicable.h"
#include "Engine/Core/Dirtiable.h"
#include "Engine/Core/ParameterContainer.h"

#include <unordered_map>

namespace mog
{
	namespace network
	{
		class NetworkComponent : public Component, public Dirtiable
		{
		public:
			NetworkComponent(ID id, const GameObject *owner);
			~NetworkComponent();

			void addVariable(const std::string &name, Replicable *var);
			void removeVariable(const std::string &name);
			void removeAllVariables();
			bool hasVarialbe(const std::string &name);

			void addSelfToGame(Game *g);

			void writeReplications(Buffer *buffer, bool dirtyOnly = false) const;
			void readReplications(const Buffer *buffer);

			bool isDirty() const override;
			void setDirty(bool dirty) override;


		private:
			std::unordered_map<std::string, Replicable*> replicationVars;
		};
	}
}
