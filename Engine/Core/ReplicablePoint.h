#pragma once
#include "Engine/Core/Point.h"
#include "Engine/Core/Replicable.h"

namespace mog
{
	class ReplicablePoint :
		public Point, public Replicable
	{
	public:
		ReplicablePoint();
		ReplicablePoint(float x, float y);

		~ReplicablePoint();

		ReplicablePoint &ReplicablePoint::operator= (const Point &);

		void read(const Buffer *buffer) override;
		void write(Buffer *buffer) const override;

		void setX(float x) override;
		void setY(float y) override;

		void setValue(Replicable *r) override;

		Replicable * clone() const override
		{
			return new ReplicablePoint(getX(), getY());
		}

		void add(Replicable *r) override;
		void minus(Replicable *r) override;
		void multiply(float r) override;


		ReplicablePoint operator*(float f)
		{
			return ReplicablePoint(getX() *f, getY() *f);
		}
	};
}

