
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "ExplosionBall.h"



ExplosionBall::ExplosionBall( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite, b2World* pWorld, float density): GameObjectBird(name, gSprite, dSprite, pWorld, density)
{
	cnt = 7;
}

void ExplosionBall::onMouseAction()
{

}

void ExplosionBall::launch()
{

}

void ExplosionBall::hit()
{
	
}

void ExplosionBall::trail()
{

}

void ExplosionBall::update2()
{
	cnt--;
	if (cnt<0)
		this->active = false;
}