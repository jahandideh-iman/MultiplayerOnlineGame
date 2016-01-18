#pragma once

#include <string>
#include "Engine/Core/SerializablePrimitive.h"



namespace mog
{
	class Point
	{
	public:
		Point(int x, int y)
		{
			this->x = x; this->y = y;
		}
		Point(){}
		int x = 0;
		int y = 0;
	};

	typedef std::string ID;

	typedef SerializablePrimitive<int> Integer;
	//typedef PrimiteSerilizable<float> Float;
	//typedef PrimiteSerilizable<double> Double;
}