
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "BlackBird.h"
#include "Color.h"
#include "ExplosionBall.h"

BlackBird::BlackBird( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite, b2World* pWorld, float density): GameObjectBird(name, gSprite, dSprite, pWorld, density)
{
	b1= 0;
	countdown = 60;
	counting = false;
	//b2=0;
}

void BlackBird::setWorld(b2World* world)
{
	pWorld = world;
}


void BlackBird::fireParticle(float x, float y)
{

	GameSprite *pBirdSprite = new GameSprite( SpriteBatchName::SpriteBatch_Moving,SpriteName::Sprite_Bird, ImageName::BLANK, Rect(pos.x+(x*15), pos.y+(y*15), 15, 15) );
	CircleSprite *pBirdCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Color(Yellow), Rect(pos.x+(x*15), pos.y+(y*15), 15, 15));
	b1 = new ExplosionBall(GameObjectName::GameObject_Bird, pBirdSprite, pBirdCircle, pWorld,60);

	b1->pGameSprite->spriteModel->SwapImage(ImageName::Name::BLANK);
	b1->bState = NORMAL2;

	b2Vec2 tmp(x, y);
	tmp *= 75;
	b1->pBody->ApplyLinearImpulse( tmp, pBody->GetWorldCenter(), true );
}
void BlackBird::onMouseAction()
{
	counting = true;
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_BlackBird2);
}

void BlackBird::Explode()
{
	fireParticle(1.0f, 0.0f);
	fireParticle(1.0f, 1.0f);
	fireParticle(0.0f, 1.0f);
	fireParticle(1.0f, -1.0f);
	fireParticle(-1.0f, -1.0f);
	fireParticle(-1.0f, 1.0f);
	fireParticle(-1.0f, 0.0f);
	fireParticle(0.0f, -1.0f);
	this->active  = false;
	GameSprite* b = new GameSprite( SpriteBatchName::SpriteBatch_Moving,SpriteName::Sprite_Bird, ImageName::Image_Bang, Rect(pos.x, pos.y, 60, 60) );
	smokeTrail.push_back(b);
	markForDelete();
	Sound::getSoundEngine()->play2D("Explosion.mp3", false, false, true);
}

void BlackBird::update2()
{
	if (counting)
	{
		countdown--;
		if (countdown < 0)
			Explode();
	}
}

void BlackBird::launch()
{
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_BlackBird1);
	launchSound = Sound::getSoundEngine()->play2D("Blackflying.mp3", false, false, true);

}

void BlackBird::hit()
{
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_BlackBird1);
	launchSound = Sound::getSoundEngine()->play2D("black collision a1.mp3", false, false, true);
}

BlackBird::~BlackBird()
{

}