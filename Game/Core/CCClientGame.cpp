#include "CCClientGame.h"
#include "Engine/Network/NetworkManager.h"
#include "Engine/Network/InternetAddress.h"
#include "Engine/Network/Messages/JoinMessage.h"
#include "Engine/Network/UDPGameSocket.h"
#include "Engine/Network/Messages/LeaveMessage.h"

USING_NS_CC;

using mog::network::JoinMessage;
using mog::network::NetworkManager;
using mog::network::InternetAddress;
using mog::network::LeaveMessage;

using mog::CCClientGame;

Scene* CCClientGame::createScene(std::string address, unsigned portNumber)
{
	auto scene = Scene::create();

	auto layer = CCClientGame::create(address, portNumber);

	scene->addChild(layer);

	return scene;
}

bool CCClientGame::init(std::string address, unsigned portNumber)
{
	unsigned addressNumber = ntohl(inet_addr(address.c_str()));
	
	setServerAddress(InternetAddress(addressNumber, portNumber));

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = getVisibleSize();
	Vec2 origin = getVisibleOrigin();
	joinServerButton = MenuItemImage::create(
		"JoinButton.png",
		"JoinButton.png",
		CC_CALLBACK_1(CCClientGame::joinServer, this));

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


	getNetworkManager()->setSocket(new network::UDPGameSocket());
	getNetworkManager()->setPort(0);



	return true;
}


void CCClientGame::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
	getNetworkManager()->sendMessage(LeaveMessage(playerName), getServerAddress());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void CCClientGame::update(float dt)
{
	network::ClientGame::update(dt);
}

void CCClientGame::joinServer(Ref* pSender)
{
	getNetworkManager()->sendMessage(JoinMessage(playerName), getServerAddress());
	joinServerButton->setVisible(false);
}

CCClientGame * mog::CCClientGame::create(std::string address, unsigned portNumber)
{
	CCClientGame *pRet = new(std::nothrow) CCClientGame();
	if (pRet && pRet->init(address,portNumber))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

