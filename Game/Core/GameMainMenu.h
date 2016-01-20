#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

namespace mog
{
	class GameMainMenu : public cocos2d::Layer
	{
	public:
		static cocos2d::Scene* createScene();

		virtual bool init();

		void menuCloseCallback(cocos2d::Ref* pSender);

		void startServer(Ref* pSender);

		void startClient(Ref* pSender);

		CREATE_FUNC(GameMainMenu);
	};
}
#endif // __HELLOWORLD_SCENE_H__
