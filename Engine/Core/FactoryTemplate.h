#pragma once

#include "Engine/Core/Object.h"
#include "Engine/Core/SingletonTemplate.h"
#include <assert.h>

namespace mog
{ 


	class Constructor  
	{
	public:
		virtual Object *create() = 0;
	};

	template<class T, class B> 
	class ConstructorT : public Constructor {
		B *create() override { return new T(); }
	};



	template<class T, class B>
	class FactoryTemplate : public SingletonTemplate<T>
	{
	public:

		template<class O>
		void setObject()
		{
			constructor = new ConstructorT<O,B>();
		}

		bool isSet(){
			return constructor != nullptr;
		}

		B *create()
		{
			B * obj = dynamic_cast<B *> (constructor->create());
			assert(obj != nullptr);
			return obj;
		}

	protected:
		FactoryTemplate(){}
		virtual ~FactoryTemplate(){ delete constructor; }

	private:
		Constructor *constructor = nullptr;
	};
}