#pragma once

#include <string>
#include "Engine/Core/ReplicablePrimitive.h"
#include "Engine/Core/ReplicablePoint.h"
#include "Engine/Core/Point.h"



namespace mog
{


	typedef std::string ID;

	typedef ReplicablePrimitive<int> Integer;
	typedef ReplicablePrimitive<int> Float;

	typedef ReplicablePoint Position;
	typedef ReplicablePoint Vector;
	//typedef PrimiteSerilizable<float> Float;
	//typedef PrimiteSerilizable<double> Double;
}