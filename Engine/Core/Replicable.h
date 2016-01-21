#pragma  once

#include "Engine/Core/Serializable.h"
#include "Engine/Core/Dirtiable.h"

namespace mog
{
	class Replicable: public Serializable, public Dirtiable
	{

	};
}