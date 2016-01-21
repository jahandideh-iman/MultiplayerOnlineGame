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

		virtual void setX(float x)
		{
			this->x = x;
		}

		virtual void setY(float y)
		{
			this->y = y;
		}

		float getX() const { return x; }
		float getY() const { return y; }

		Point operator*(float f) 
		{
			return Point(x *f, y*f);
		}

		Point operator+(Point &other)
		{
			return Point(x + other.x, y + other.y);
		}

		void normalize()
		{
			auto s = x * x + y *y;
			x = x / s;
			y = y / s;
		}
	private:
		float x = 0;
		float y = 0;
	};
}