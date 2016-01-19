#include "Bullet.h"

#include "SpriteComponent.h"

mog::Bullet::Bullet()
{
	addComponent(new SpriteComponent("sprite", this, "bullet.png"));

}

mog::Bullet::Bullet(Pawn *shooter, Float r, Point p)
{
	this->shooter = shooter;
	setPosition(p);
	setVelocity(Vector(0, 1) * speed);
}

mog::Bullet::~Bullet()
{

}

void mog::Bullet::update(float dt)
{
	NetworkGameObject::update(dt);
	if (getVelocity().x != 0 || getVelocity().y != 0)
		setRoation(atan2(getVelocity().x, getVelocity().y) * 180 / M_PI); //WARNING: Why the parameters are inverse
}