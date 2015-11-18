#pragma once


namespace mog
{
	class Game;

	class Component
	{
	public:
		Component();
		~Component();

		virtual void addSelfToGame(Game *g) = 0;
	};
}
