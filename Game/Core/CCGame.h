#pragma once

#include "cocos2d.h"

#define UPDATE_RATE 30
namespace mog
{


	class CCGame : public cocos2d::Layer
	{
	public:
		CCGame();
		~CCGame();

		cocos2d::Size getVisibleSize() const;

		cocos2d::Vec2 getVisibleOrigin() const;

		cocos2d::Rect getVisibleViewRect() const;
	};

	class CCNetworkGame
	{
	public:

		CCNetworkGame(CCGame * game)
		{
			this->game = game;
		}

		CCGame * getGame()
		{
			return game;
		}

	private:
		CCGame *game = nullptr;

	};
}

