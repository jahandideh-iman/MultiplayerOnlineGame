#pragma once

namespace mog
{
	template<class T>
	class SingletonTemplate
	{
	public:
		static T *get()
		{
			if (factory == nullptr)
				factory = new T();
			return factory;
		}
		static void clear()
		{
			delete factory;
			factory = nullptr;
		}
	protected:
		SingletonTemplate(){};
		virtual ~SingletonTemplate(){};

		static T * factory;

	};

	template <typename T>
	T* SingletonTemplate<T>::factory = nullptr;
}