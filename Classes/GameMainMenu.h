#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class GameMainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);

	void StartServer(Ref* pSender);

	void StartClient(Ref* pSender);
    
	CREATE_FUNC(GameMainMenu);
};

#endif // __HELLOWORLD_SCENE_H__
