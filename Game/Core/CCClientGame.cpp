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

Scene* CCClientGame::createScene()
{
	auto scene = Scene::create();

	auto layer = CCClientGame::create();

	scene->addChild(layer);

	return scene;
}

bool CCClientGame::init()
{
	if (!Layer::init())
	{
		return false;
	}

	clientGame = new CustomClientGame(this);

	Size visibleSize = getVisibleSize();
	Vec2 origin = getVisibleOrigin();

	std::string pNormalSprite = "EditBox.png";
	this->serverAddressEditBox = ui::EditBox::create(Size(160, 50), ui::Scale9Sprite::create(pNormalSprite));
	serverAddressEditBox->setPosition(Vec2(origin.x + visibleSize.width *0.47, origin.y + visibleSize.height * 0.6));
	serverAddressEditBox->setFontName("Paint Boy");
	serverAddressEditBox->setFontSize(20);
	serverAddressEditBox->setFontColor(Color3B::WHITE);
	serverAddressEditBox->setPlaceHolder("IP");
	serverAddressEditBox->setPlaceholderFontColor(Color3B::WHITE);
	serverAddressEditBox->setMaxLength(15);
	serverAddressEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	serverAddressEditBox->setText("127.0.0.1");
	addChild(serverAddressEditBox);

	this->serverPortEditBox = ui::EditBox::create(Size(60, 50), ui::Scale9Sprite::create(pNormalSprite));
	serverPortEditBox->setPosition(Vec2(origin.x + serverAddressEditBox->getPosition().x + serverAddressEditBox->getContentSize().width/2 + visibleSize.width *0.05, origin.y + visibleSize.height * 0.6));
	serverPortEditBox->setFontName("Paint Boy");
	serverPortEditBox->setFontSize(20);
	serverPortEditBox->setFontColor(Color3B::WHITE);
	serverPortEditBox->setPlaceHolder("Port");
	serverPortEditBox->setPlaceholderFontColor(Color3B::WHITE);
	serverPortEditBox->setMaxLength(8);
	serverPortEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	serverPortEditBox->setText("8082");
	//portEditBox->setDelegate(this);
	addChild(serverPortEditBox);

	joinServerButton = MenuItemImage::create(
		"JoinButton.png",
		"JoinButton_Pressed.png",
		CC_CALLBACK_1(CCClientGame::joinServer, this));

	joinServerButton->setPosition(Vec2(origin.x + visibleSize.width * 0.5,
		origin.y + visibleSize.height * 0.4 ));

	auto menu = Menu::create(joinServerButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto label = Label::createWithTTF("Client", "fonts/arial.ttf", 24);

	label->setColor(Color3B::GREEN);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 20);

	this->scheduleUpdate();

	clientGame->getNetworkManager()->setSocket(new network::UDPGameSocket());
	clientGame->getNetworkManager()->setPort(0);

	return true;
}

void CCClientGame::update(float dt)
{
	clientGame->update(dt);
}

void CCClientGame::joinServer(Ref* pSender)
{
	unsigned addressNumber = ntohl(inet_addr(serverAddressEditBox->getText()));
	unsigned portNumber = atoi(serverPortEditBox->getText());

	serverAddressEditBox->setVisible(false);
	serverPortEditBox->setVisible(false);
	joinServerButton->setVisible(false);
	
	clientGame->setServerAddress(InternetAddress(addressNumber, portNumber));
	clientGame->getNetworkManager()->setUpdateRate(UPDATE_RATE);
	clientGame->getNetworkManager()->sendMessage(JoinMessage(playerName), clientGame->getServerAddress());
}
