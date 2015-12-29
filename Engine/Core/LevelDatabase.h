#pragma once

#include "Engine/Core/Types.h"
#include <unordered_map>

#define REGISTER_LEVEL(T) \
	mog::Level* level_##T = new T(); \
	mog::LevelDatabase::get()->registerLevel(level_##T); \

namespace mog
{
	class Level;

	class LevelDatabase
	{
	public:

		static LevelDatabase *get();
		static void clear();

		Level *find(ID id);

		void registerLevel(Level *m);
	private:
		LevelDatabase();
		~LevelDatabase();

	private:
		static LevelDatabase *db;

		std::unordered_map<ID, Level *> map;

	};
}