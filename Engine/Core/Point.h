#pragma once

namespace mog
{
	class Point
	{
	public:
		Point(float x, float y)
		{
			this->x = x; this->y = y;
		}
		Point(){}
		float x = 0;
		float y = 0;

		Point operator*(float f) 
		{
			return Point(x *f, y*f);
		}

		Point operator+(Point &other)
		{
			return Point(x + other.x, y + other.y);
		}
	};
}