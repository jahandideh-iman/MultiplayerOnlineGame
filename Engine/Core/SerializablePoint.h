#pragma once
#include "Engine/Core/Point.h"
#include "Engine/Core/Serializable.h"

namespace mog
{
	class SerializablePoint :
		public Point, public Serializable
	{
	public:
		SerializablePoint();
		SerializablePoint(float x, float y);
		~SerializablePoint();

		SerializablePoint &SerializablePoint::operator= (const Point &);

		void read(const Buffer *buffer) override;
		void write(Buffer *buffer) const override;
	};
}

