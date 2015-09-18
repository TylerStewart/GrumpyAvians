
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "WhiteBird.h"
#include "Color.h"


WhiteBird::WhiteBird( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite, b2World* pWorld, float density): GameObjectBird(name, gSprite, dSprite, pWorld, density)
{

}

void WhiteBird::setWorld(b2World* world)
{
	pWorld = world;
}

void WhiteBird::onMouseAction()
{
	GameObjectBird* egg;

	GameSprite *pBirdSprite = new GameSprite( SpriteBatchName::SpriteBatch_Moving,SpriteName::Sprite_Bird, ImageName::Image_Egg, Rect(pos.x, pos.y, 20, 25) );
	CircleSprite *pBirdCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Color(Yellow), Rect(pos.x, pos.y-10*2, 20, 20));
	egg = new GameObjectBird(GameObjectName::GameObject_Bird, pBirdSprite, pBirdCircle,pWorld, 50.0f );

	egg->bState = NORMAL2;
	printf("%f \n", egg->pos.y);
	b2Vec2 tmp(0, -1);
	tmp *= 50;
	egg->pBody->ApplyLinearImpulse( tmp, pBody->GetWorldCenter(), true );

	b2Vec2 tmp1(0, 1);
	tmp1 *= 100;
	pBody->ApplyLinearImpulse( tmp1, pBody->GetWorldCenter(), true );
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_WhiteBird2);

}


void WhiteBird::launch()
{
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_WhiteBird1);
	launchSound = Sound::getSoundEngine()->play2D("WhiteFlying.mp3", false, false, true);
}

void WhiteBird::hit()
{
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_WhiteBird3);
	launchSound = Sound::getSoundEngine()->play2D("white collision a1.mp3", false, false, true);
}