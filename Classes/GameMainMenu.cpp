#include "GameMainMenu.h"
#include "ServerGame.h"
#include "ClientGame.h"


USING_NS_CC;

Scene* GameMainMenu::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameMainMenu::create();

    scene->addChild(layer);

    return scene;
}

bool GameMainMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto serverGameItem = MenuItemImage::create(
		"ServerButton.png",
		"ServerButton.png",
		CC_CALLBACK_1(GameMainMenu::StartServer, this));

	auto clientGameItem = MenuItemImage::create(
		"clientButton.png",
		"clientButton.png",
		CC_CALLBACK_1(GameMainMenu::StartClient, this));



	serverGameItem->setPosition(Vec2(origin.x + visibleSize.width * 0.5 - serverGameItem->getContentSize().width / 2,
		origin.y + visibleSize.height * 0.6 - serverGameItem->getContentSize().height / 2));


	clientGameItem->setPosition(Vec2(origin.x + visibleSize.width * 0.5 - clientGameItem->getContentSize().width / 2,
		origin.y + visibleSize.height * 0.4 - clientGameItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
	auto menu = Menu::create(serverGameItem, clientGameItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    
    auto label = Label::createWithTTF("Main Menu", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    
    return true;
}


void GameMainMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameMainMenu::StartServer(Ref* pSender)
{
	CCDirector::getInstance()->replaceScene(ServerGame::createScene());
}

void GameMainMenu::StartClient(Ref* pSender)
{
	CCDirector::getInstance()->replaceScene(ClientGame::createScene());

}
