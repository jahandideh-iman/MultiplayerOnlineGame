#include "CCServerGame.h"
#include "Engine/Network/NetworkManager.h"
#include "GameLevel.h"
#include "Engine/Network/Messages/LoadLevelMessage.h"
#include "Engine/Network/Messages/ReplicateInstanceMessage.h"
#include "Core/Pawn.h"
#include "Engine/Network/UDPGameSocket.h"

USING_NS_CC;

using namespace mog;

Scene* CCServerGame::createScene()
{
	auto scene = Scene::create();

	auto layer = CCServerGame::create();

	scene->addChild(layer);

	return scene;
}

bool CCServerGame::init()
{


	if (!Layer::init())
	{
		return false;
	}

	serverGame = new CustomServerGame(this);

	Size visibleSize = getVisibleSize();
	Vec2 origin = getVisibleOrigin();

	startListeningButton = MenuItemImage::create(
		"StartButton.png",
		"StartButton_Pressed.png",
		CC_CALLBACK_1(CCServerGame::startListening, this));


	startListeningButton->setPosition(Vec2(origin.x + visibleSize.width * 0.5,
		origin.y + visibleSize.height * 0.6));

	auto menu = Menu::create(startListeningButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto label = Label::createWithTTF("Server", "fonts/arial.ttf", 24);

	label->setColor(Color3B::GREEN);

	auto backGround = cocos2d::Sprite::create("background.png");
	backGround->setRotation(90);
	this->addChild(backGround,-1);


	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	std::string pNormalSprite = "EditBox.png";
	this->serverListenPortEditBox = ui::EditBox::create(Size(60, 50), ui::Scale9Sprite::create(pNormalSprite));
	serverListenPortEditBox->setPosition(Vec2(origin.x + visibleSize.width *0.5, origin.y + visibleSize.height * 0.4));
	serverListenPortEditBox->setFontName("Paint Boy");
	serverListenPortEditBox->setFontSize(20);
	serverListenPortEditBox->setFontColor(Color3B::WHITE);
	serverListenPortEditBox->setPlaceHolder("Port");
	serverListenPortEditBox->setPlaceholderFontColor(Color3B::WHITE);
	serverListenPortEditBox->setMaxLength(80);
	serverListenPortEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	serverListenPortEditBox->setText("8082 ");
	addChild(serverListenPortEditBox);



	return true;
}

void CCServerGame::update(float dt)
{
	serverGame->update(dt);
}

void mog::CCServerGame::startListening(cocos2d::Ref* pSender)
{
	startListeningButton->setVisible(false);
	serverListenPortEditBox->setVisible(false);

	unsigned portNumber = atoi(serverListenPortEditBox->getText());
	serverGame->getNetworkManager()->setSocket(new network::UDPGameSocket());
	serverGame->getNetworkManager()->setPort(portNumber);

	serverGame->getNetworkManager()->setUpdateRate(UPDATE_RATE);

	this->scheduleUpdate();
}

mog::CCServerGame::~CCServerGame()
{
	delete serverGame;
}
