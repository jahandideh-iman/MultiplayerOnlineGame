#include "ServerGame.h"
#include "GameSocket.h"
#include "InternetAddress.h"

USING_NS_CC;


ServerGame::~ServerGame(){

}

Scene* ServerGame::createScene()
{
	auto scene = Scene::create();

	auto layer = ServerGame::create();

	scene->addChild(layer);

	return scene;
}

bool ServerGame::init()
{

	
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();





	auto label = Label::createWithTTF("Server", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	this->scheduleUpdate();

	//serverSocket = new GameSocket();
	//serverSocket->Open(8082);

	return true;
}


void ServerGame::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void ServerGame::updateNetwork()
{
	CCLOG("------------------------- Updating Network -----------------------");
	InternetAddress senderAddress;
	//serverSocket->Receive(senderAddress, 
}

void ServerGame::update(float dt)
{
	updateNetwork();
}
