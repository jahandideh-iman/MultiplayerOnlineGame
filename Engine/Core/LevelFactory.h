#pragma once

#include "Engine/Core/FactoryTemplate.h"

#include "Engine/Core/Level.h"

namespace mog
{

	class LevelFactory : public FactoryTemplate<LevelFactory, Level>
	{
	public:
		LevelFactory();
		~LevelFactory();
	};

	LevelFactory * LevelFactory::factory = nullptr;
}

