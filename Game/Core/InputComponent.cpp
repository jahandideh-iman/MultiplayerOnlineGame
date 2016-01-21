#include "InputComponent.h"
#include "Engine/Network/ServerGame.h"
#include "CCGame.h"


mog::InputComponent::InputComponent(ID id, const GameObject *owner) : Component(id,owner)
{
}


mog::InputComponent::~InputComponent()
{
	if (ccGame != nullptr)
		ccGame->getEventDispatcher()->removeEventListenersForTarget(this);
}

void mog::InputComponent::addOnPressAction(cocos2d::EventKeyboard::KeyCode key, Action action)
{
	onPressActions[key] = action;
}

void mog::InputComponent::addOnReleaseAction(cocos2d::EventKeyboard::KeyCode key, Action action)
{
	onReleaseActions[key] = action;
}

void mog::InputComponent::addSelfToGame(Game *g)
{
	auto networkGame = dynamic_cast<mog::network::ServerGame*> (g);

	//Not added to server
	if (networkGame != nullptr)
		return;

	auto ccNetGame = dynamic_cast<CCNetworkGame*> (g);
	assert(ccNetGame != nullptr);

	ccGame = ccNetGame->getGame();

	auto eventListener = cocos2d::EventListenerKeyboard::create();

	eventListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		auto actionPair = onPressActions.find(keyCode);
		if (actionPair != onPressActions.end())
			actionPair->second();
	};

	eventListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		auto actionPair = onReleaseActions.find(keyCode);
		if (actionPair != onReleaseActions.end())
			actionPair->second();
	};

	ccGame->addChild(this);
	ccGame->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}


