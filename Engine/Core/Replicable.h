#pragma  once

#include "Engine/Core/Serializable.h"
#include "Engine/Core/Dirtiable.h"

namespace mog
{
	class Replicable: public Serializable, public Dirtiable
	{
	public:
		virtual Replicable* clone() const = 0;
		virtual void add(Replicable *) = 0;
		virtual void minus(Replicable *) = 0;
		virtual void multiply(float m) = 0;
		virtual void setValue(Replicable *) = 0;

		virtual ~Replicable() {}
	};
}