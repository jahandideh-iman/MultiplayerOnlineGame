#pragma once
#include "Engine/Core/Types.h"
#include "Engine/Core/Serializable.h"

namespace mog
{
	class SerializablePoint :
		public Point, public Serializable
	{
	public:
		SerializablePoint();
		SerializablePoint(int x, int y);
		~SerializablePoint();

		SerializablePoint &SerializablePoint::operator= (const Point &);

		void read(const Buffer *buffer) override;
		void write(Buffer *buffer) const override;
	};
}

