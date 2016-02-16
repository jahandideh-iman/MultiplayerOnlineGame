#include "Bullet.h"

#include "SpriteComponent.h"
#include "Engine/Network/ServerGame.h"
#include "Core/Macros.h"


mog::Bullet::Bullet()
{
	initial();
}

mog::Bullet::Bullet(Pawn *shooter, Float r, Point p)
{
	initial();
	this->shooter = shooter;
	setPosition(p);
	float x = cos(r.getValue() * M_PI / 180);
	float y = sin(r.getValue() * M_PI / 180);

	Vector v(x, y);
	v.normalize();
	setVelocity(v * speed);

}

mog::Bullet::~Bullet()
{

}

void mog::Bullet::onOutOfView()
{
	if (dynamic_cast<network::ServerGame*>(getOwner()) != nullptr)
		getOwner()->removeGameObjectAtEndOfUpdate(this);
}

void mog::Bullet::onAddedToGame(Game *game)
{
	NetworkGameObject::onAddedToGame(game);
}

void mog::Bullet::initial()
{
	auto spriteComp = new SpriteComponent("sprite", this, "bullet.png");
	spriteComp->addOutOfViewCallback(std::bind(&mog::Bullet::onOutOfView, this));
	addComponent(spriteComp);
}

void mog::Bullet::updatePosition(float dt)
{
	if (PREDICION_ON)
		GameObject::updatePosition(dt);
	else
	{
		if (dynamic_cast<network::NetworkGame *> (getOwner()) == nullptr)
			GameObject::updatePosition(dt);
		else
		{
			if (dynamic_cast<network::ServerGame *> (getOwner()) != nullptr)
				GameObject::updatePosition(dt);
		}
	}
}
