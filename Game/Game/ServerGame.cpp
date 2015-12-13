#include "ServerGame.h"
#include "Network/NetworkManager.h"
#include "GameLevel.h"
#include "Network/LoadLevel.h"
#include "Network/ReplicateInstance.h"
#include "Game/Pawn.h"

USING_NS_CC;

using namespace mog;

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

	
	getNetworkManager()->setPort(8082);


	loadLevel(new GameLevel());
	return true;
}


void ServerGame::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void ServerGame::update(float dt)
{
	network::ServerGame::update(dt);
}
