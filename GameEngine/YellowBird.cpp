
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "YellowBird.h"



YellowBird::YellowBird( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite, b2World* pWorld, float density): GameObjectBird(name, gSprite, dSprite, pWorld, density)
{

}

void YellowBird::onMouseAction()
{
	b2Vec2 tmp =  15 * dir;
	pBody->ApplyLinearImpulse( tmp, pBody->GetWorldCenter(), true );
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_YellowBird2);
}

void YellowBird::launch()
{
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_YellowBird1);
	launchSound = Sound::getSoundEngine()->play2D("yellow flying.mp3", false, false, true);
}

void YellowBird::hit()
{
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_YellowBird3);
	launchSound = Sound::getSoundEngine()->play2D("yellow collision a1.mp3", false, false, true);
}