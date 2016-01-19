#include "GameMainMenu.h"
#include "ServerGame.h"
#include "ClientGame.h"



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
		"ServerButton.png",
		CC_CALLBACK_1(GameMainMenu::StartServer, this));

	std::string pNormalSprite = "EditBox.png";
	this->serverListenPortEditBox = ui::EditBox::create(Size(50, 100), ui::Scale9Sprite::create(pNormalSprite));
	serverListenPortEditBox->setPosition(Vec2(origin.x + visibleSize.width *0.7, origin.y + visibleSize.height * 0.6));
	serverListenPortEditBox->setFontName("Paint Boy");
	serverListenPortEditBox->setFontSize(10);
	serverListenPortEditBox->setFontColor(Color3B::BLACK);
	serverListenPortEditBox->setPlaceHolder("Port");
	serverListenPortEditBox->setPlaceholderFontColor(Color3B::WHITE);
	serverListenPortEditBox->setMaxLength(8);
	serverListenPortEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	serverListenPortEditBox->setText("8082");
	//portEditBox->setDelegate(this);
	addChild(serverListenPortEditBox);

	auto clientGameItem = MenuItemImage::create(
		"clientButton.png",
		"clientButton.png",
		CC_CALLBACK_1(GameMainMenu::StartClient, this));

	this->serverAddressEditBox = ui::EditBox::create(Size(50, 100), ui::Scale9Sprite::create(pNormalSprite));
	serverAddressEditBox->setPosition(Vec2(origin.x + visibleSize.width *0.6, origin.y + visibleSize.height * 0.4));
	serverAddressEditBox->setFontName("Paint Boy");
	serverAddressEditBox->setFontSize(10);
	serverAddressEditBox->setFontColor(Color3B::BLACK);
	serverAddressEditBox->setPlaceHolder("IP");
	serverAddressEditBox->setPlaceholderFontColor(Color3B::WHITE);
	serverAddressEditBox->setMaxLength(15);
	serverAddressEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	serverAddressEditBox->setText("127.0.0.1");
	addChild(serverAddressEditBox);

	this->serverPortEditBox = ui::EditBox::create(Size(50, 100), ui::Scale9Sprite::create(pNormalSprite));
	serverPortEditBox->setPosition(Vec2(origin.x + visibleSize.width *0.8, origin.y + visibleSize.height * 0.4));
	serverPortEditBox->setFontName("Paint Boy");
	serverPortEditBox->setFontSize(10);
	serverPortEditBox->setFontColor(Color3B::BLACK);
	serverPortEditBox->setPlaceHolder("Port");
	serverPortEditBox->setPlaceholderFontColor(Color3B::WHITE);
	serverPortEditBox->setMaxLength(8);
	serverPortEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	serverPortEditBox->setText("8082");
	//portEditBox->setDelegate(this);
	addChild(serverPortEditBox);


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
	CCDirector::getInstance()->replaceScene(CCServerGame::createScene(atoi(serverListenPortEditBox->getText())));
}

void GameMainMenu::StartClient(Ref* pSender)
{
	CCDirector::getInstance()->replaceScene(CCClientGame::createScene(serverAddressEditBox->getText(), atoi(serverPortEditBox->getText())));
}
