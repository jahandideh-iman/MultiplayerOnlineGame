#include "ClientGame.h"
#include "Network/NetworkManager.h"
#include "Network/InternetAddress.h"
#include "Join.h"
#include "Engine/GlobalData.h"

USING_NS_CC;

using mog::network::Join;
using mog::network::NetworkManager;
using mog::network::InternetAddress;
using mog::ClientGame;

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

	auto joinServerButton = MenuItemImage::create(
		"JoinButton.png",
		"JoinButton.png",
		CC_CALLBACK_1(ClientGame::joinServer, this));

	joinServerButton->setPosition(Vec2(origin.x + visibleSize.width * 0.5 - joinServerButton->getContentSize().width / 2,
		origin.y + visibleSize.height * 0.4 - joinServerButton->getContentSize().height / 2));

	auto menu = Menu::create(joinServerButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	auto label = Label::createWithTTF("Client", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	this->scheduleUpdate();


	NetworkManager::get()->setPort(0);

	return true;
}


void ClientGame::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void ClientGame::update(float dt)
{
	NetworkManager::get()->update(dt);
}

void ClientGame::joinServer(Ref* pSender)
{
	
	InternetAddress address(127, 0, 0, 1, 8082);
	NetworkManager::get()->sendMessage(Join(), address);
	//char* message = "hello";
	//socket->Send(address, message, sizeof(message) );
}
