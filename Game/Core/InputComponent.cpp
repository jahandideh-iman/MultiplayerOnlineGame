#include "InputComponent.h"
#include "Engine/Network/ServerGame.h"



mog::InputComponent::InputComponent(ID id, const GameObject *owner) : Component(id,owner)
{
}


mog::InputComponent::~InputComponent()
{

}

void mog::InputComponent::addAction(cocos2d::EventKeyboard::KeyCode key, Action action)
{
	actions[key] = action;
}

void mog::InputComponent::addSelfToGame(Game *g)
{
	auto networkGame = dynamic_cast<mog::network::ServerGame*> (g);

	//Not added to server
	if (networkGame != nullptr)
		return;

	auto cocosGame = dynamic_cast<cocos2d::Layer*> (g);
	assert(cocosGame != nullptr);

	auto eventListener = cocos2d::EventListenerKeyboard::create();
	eventListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		auto actionPair = actions.find(keyCode);
		if (actionPair != actions.end())
			actionPair->second();
	};

	cocosGame->addChild(this);
	cocosGame->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener,this);
}
