#include "GameMainMenu.h"
#include "CCServerGame.h"
#include "CCClientGame.h"



USING_NS_CC;

using mog::GameMainMenu;

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
		"ServerButton_Pressed.png",
		CC_CALLBACK_1(GameMainMenu::startServer, this));

	auto clientGameItem = MenuItemImage::create(
		"ClientButton.png",
		"ClientButton_Pressed.png",
		CC_CALLBACK_1(GameMainMenu::startClient, this));

	serverGameItem->setPosition(Vec2(origin.x + visibleSize.width * 0.5 /*- serverGameItem->getContentSize().width / 2*/,
		origin.y + visibleSize.height * 0.6));


	clientGameItem->setPosition(Vec2(origin.x + visibleSize.width * 0.5/* - clientGameItem->getContentSize().width / 2*/,
		origin.y + visibleSize.height * 0.4 ));


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

void GameMainMenu::startServer(Ref* pSender)
{
	CCDirector::getInstance()->replaceScene(CCServerGame::createScene());
}

void GameMainMenu::startClient(Ref* pSender)
{
	CCDirector::getInstance()->replaceScene(CCClientGame::createScene());
}
