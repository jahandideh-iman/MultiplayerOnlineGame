#pragma once

namespace mog
{
	class Buffer;
	class Serializable
	{
	public:
		virtual void read(const Buffer *buffer) = 0;
		virtual void write(Buffer *buffer) const = 0;
	};
}