#pragma  once

#include "MockGameObject.h"

#include "Engine/Core/Level.h"
#include "Engine/Core/Macros.h"

namespace mog
{
	class MockLevel : public Level
	{
	public:
		virtual void initialGameObjects(Game * game) override
		{
			addGameObject(new MockGameObject("Obj1"));
			addGameObject(new MockGameObject("Obj2"));
		}


		//virtual ID getID() const override{ return "MockLevel"; }
		AUTOID(MockLevel, getID);

	};

}