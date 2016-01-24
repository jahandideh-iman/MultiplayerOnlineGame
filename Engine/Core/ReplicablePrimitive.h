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

		Replicable *clone() const override
		{
			return new ReplicablePrimitive<T>(getValue());
		}

		void add(Replicable *r) override
		{
			auto pr = dynamic_cast<ReplicablePrimitive<T> *> (r);
			value += pr->getValue();
		}

		void minus(Replicable *r) override
		{
			auto pr = dynamic_cast<ReplicablePrimitive<T> *> (r);
			value -= pr->getValue();
		}

		void multiply(float m) override
		{
			value *= m;
		}

		void setValue(Replicable *r) override
		{
			auto pr = dynamic_cast<ReplicablePrimitive<T> *> (r);
			value = pr->getValue();
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
		T getValue() const { return value; }

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

	template<>
	void ReplicablePrimitive<float> ::read(const Buffer *buffer)
	{
		char *data = buffer->getData();
		value = std::stof(data);
		delete[]data;
	}

	template<>
	void ReplicablePrimitive<int> ::multiply(float m) 
	{
		value = int(value * m);
	}

	template<typename T>
	using Var = ReplicablePrimitive<T>;
}
