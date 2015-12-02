#include <string>
#include "Engine/Serializable.h"
#include "Engine/SerializablePrimitive.h"

namespace mog
{
	typedef std::string ID;

	typedef SerializablePrimitive<int> Integer;
	//typedef PrimiteSerilizable<float> Float;
	//typedef PrimiteSerilizable<double> Double;
}