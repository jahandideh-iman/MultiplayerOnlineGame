#pragma once

#include "Engine/Core/SingletonTemplate.h"
#include <vector>

namespace mog
{
	template<class T,class O,unsigned S>
	class ObjectPoolTemplate : public SingletonTemplate<T>
	{
	public:

		void getSize(unsigned size)
		{
			pool.size();
		}

		O *create()
		{

		}

		void remove(O *o)
		{

		}

	protected:
		ObjectPoolTemplate()
		{
			for (unsigned i = 0; i < S; i++)
				pool.push_back(new O());
		}
		~ObjectPoolTemplate()
		{
			while (!pool.empty())
			{
				auto it = pool.begin();
				delete *it;
				pool.erase(it);
			}
		}

	private:
		std::vector<O*> pool;


	};


}