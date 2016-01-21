#pragma once

#include "Engine/Core/Replicable.h"
#include "Engine/Core/Buffer.h"

namespace mog
{
	template<typename T>
	class ReplicablePrimitive : public Replicable
	{
	public:
		ReplicablePrimitive(T v){ setValue(v); }
		ReplicablePrimitive(T &v){ setValue(v); }
		ReplicablePrimitive(){}
		~ReplicablePrimitive(){}

		virtual void write(Buffer *buffer) const override 
		{
			buffer->write(std::to_string(value));
		}

		virtual void read(const Buffer *buffer) override {static_assert(false, "Type not supported")};

		void setValue(T v)
		{ 
			if (value != v)
			{
				this->value = v; 
				setDirty(true);
			}

		}
		T getValue(){ return value; }

		ReplicablePrimitive<T>& operator=(T const & value)
		{
			this->value = value;
			return *this;
		}

	private:
		T value;
	};



	template<>
	void ReplicablePrimitive<int> ::read(const Buffer *buffer)
	{ 
		char *data = buffer->getData();
		value = std::stoi(data);
		delete []data;
	}

	template<typename T>
	using Var = ReplicablePrimitive<T>;
}
