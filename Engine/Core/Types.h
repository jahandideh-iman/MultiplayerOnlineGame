#pragma once

#include <string>
#include "Engine/Core/SerializablePrimitive.h"
#include "Engine/Core/SerializablePoint.h"
#include "Engine/Core/Point.h"



namespace mog
{


	typedef std::string ID;

	typedef SerializablePrimitive<int> Integer;
	typedef SerializablePrimitive<int> Float;

	typedef SerializablePoint Position;
	typedef SerializablePoint Vector;
	//typedef PrimiteSerilizable<float> Float;
	//typedef PrimiteSerilizable<double> Double;
}