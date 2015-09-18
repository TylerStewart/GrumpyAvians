
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "GreenBird.h"



GreenBird::GreenBird( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite, b2World* pWorld, float density): GameObjectBird(name, gSprite, dSprite, pWorld, density)
{

}

void GreenBird::update2()
{
	if (boomtimer>0&&!first)
	{
		pBody->ApplyLinearImpulse( boom, pBody->GetWorldCenter(), true );
		boomtimer--;
	}
}

void GreenBird::onMouseAction()
{
	if (first)
	{
		b2Vec2 tmp(pBody->GetLinearVelocity().x*-1, 0);
		tmp.Normalize();
		boom=tmp;
		first = 0;
	}
	if (abs(pBody->GetLinearVelocity().x)<170)
	{
		boom *=7;
		pBody->ApplyLinearImpulse( boom, pBody->GetWorldCenter(), true );
		pBody->ApplyAngularImpulse(-10, true);
		//bState=NORMAL1;
		//printf("f% - %f \n", pBody->GetLinearVelocity().x,pBody->GetLinearVelocity().y);
	}
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_GreenBird2);
	launchSound = Sound::getSoundEngine()->play2D("boomerang_activate.mp3", false, false, true);
	
}

void GreenBird::launch()
{
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_GreenBird1);
	launchSound = Sound::getSoundEngine()->play2D("green flying.mp3", false, false, true);
}

void GreenBird::hit()
{
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_GreenBird3);
	launchSound = Sound::getSoundEngine()->play2D("green collision a1.mp3", false, false, true);
}
