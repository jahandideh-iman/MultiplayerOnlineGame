#include "CCServerGame.h"
#include "Engine/Network/NetworkManager.h"
#include "GameLevel.h"
#include "Engine/Network/Messages/LoadLevelMessage.h"
#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Core/Pawn.h"
#include "Engine/Network/UDPGameSocket.h"

USING_NS_CC;

using namespace mog;

CCServerGame::~CCServerGame(){

}

Scene* CCServerGame::createScene(unsigned portNumber)
{
	auto scene = Scene::create();

	auto layer = CCServerGame::create(portNumber);

	scene->addChild(layer);

	return scene;
}

CCServerGame * mog::CCServerGame::create(unsigned portNumber)
{
	CCServerGame *pRet = new(std::nothrow) CCServerGame();
	if (pRet && pRet->init(portNumber))
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

bool CCServerGame::init(unsigned portNumber)
{

	setPortNumber(portNumber);
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

	getNetworkManager()->setSocket(new network::UDPGameSocket());
	getNetworkManager()->setPort(portNumber);

	return true;
}


void CCServerGame::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void CCServerGame::update(float dt)
{
	network::ServerGame::update(dt);
}

void mog::CCServerGame::onPawnCreated(network::NetworkPawn *p)
{
	p->setPosition(Point(50,50));
}

void mog::CCServerGame::setPortNumber(unsigned port)
{
	this->portNumber = port;
}



