#include "CCGame.h"

USING_NS_CC;

mog::CCGame::CCGame()
{

}

mog::CCGame::~CCGame()
{

}


cocos2d::Size mog::CCGame::getVisibleSize() const
{
	return Director::getInstance()->getVisibleSize();
}

cocos2d::Vec2 mog::CCGame::getVisibleOrigin() const
{
	return Director::getInstance()->getVisibleOrigin();
}

cocos2d::Rect mog::CCGame::getVisibleViewRect() const
{
	auto origin = getVisibleOrigin();
	auto viewSize = getVisibleSize();
	return Rect(origin.x, origin.y, viewSize.width, viewSize.height);
}

