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
	float x = cos(r.getValue() * M_PI / 180);
	float y = sin(r.getValue() * M_PI / 180);

	Vector v(x, y);
	v.normalize();
	setVelocity(v * speed);
}

mog::Bullet::~Bullet()
{

}
