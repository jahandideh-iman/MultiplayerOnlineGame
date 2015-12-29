#pragma once

#include "Engine/Core/Serializable.h"
#include "Engine/Core/Buffer.h"

namespace mog
{
	template<typename T>
	class SerializablePrimitive : public Serializable
	{
	public:
		SerializablePrimitive(T v){ setValue(v); }
		SerializablePrimitive(T &v){ setValue(v); }
		SerializablePrimitive(){}
		~SerializablePrimitive(){}

		virtual void write(Buffer *buffer) const override 
		{
			buffer->write(std::to_string(value));
		}

		virtual void read(const Buffer *buffer) override {static_assert(false, "Type not supported")};

		void setValue(T v){ this->value = v; };
		T getValue(){ return value; }

		SerializablePrimitive<T>& operator=(T const & value)
		{
			m_value = value;
			return *this;
		}

	private:
		T value;
	};



	template<>
	void SerializablePrimitive<int> ::read(const Buffer *buffer){ value = std::stoi(buffer->getData()); }


	template<typename T>
	using Var = SerializablePrimitive<T>;
}
