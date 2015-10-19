#include "ClientGame.h"

USING_NS_CC;

Scene* ClientGame::createScene()
{
	auto scene = Scene::create();

	auto layer = ClientGame::create();

	scene->addChild(layer);

	return scene;
}

bool ClientGame::init()
{

	
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();





	auto label = Label::createWithTTF("Client", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	this->scheduleUpdate();

	return true;
}


void ClientGame::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void ClientGame::updateNetwork()
{
	CCLOG("------------------------- Updating Network -----------------------");
}

void ClientGame::update(float dt)
{
	updateNetwork();
}
