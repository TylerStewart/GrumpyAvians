
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "BlueBird.h"
#include "Color.h"


BlueBird::BlueBird( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite, b2World* pWorld, float density): GameObjectBird(name, gSprite, dSprite, pWorld, density)
{
	b1= 0;
	b2=0;
}

void BlueBird::setWorld(b2World* world)
{
	pWorld = world;
}

void BlueBird::onMouseAction()
{
	GameSprite* g;
	g = new GameSprite(SpriteBatchName::SpriteBatch_Background2, SpriteName::Sprite_Smoke, ImageName::Image_Smoke,Rect(this->pos.x, this->pos.y,25, 25) );
	smokeTrail.push_back(g);

	b2Vec2 offset(pBody->GetLinearVelocity().y, pBody->GetLinearVelocity().x);
	offset.Normalize();


	GameSprite *pBirdSprite = new GameSprite( SpriteBatchName::SpriteBatch_Moving,SpriteName::Sprite_Bird, ImageName::Image_BlueBird, Rect(pos.x-offset.x*15, pos.y+offset.y*15, 15, 15) );
	CircleSprite *pBirdCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Color(Yellow), Rect(pos.x-offset.x*15, pos.y+offset.y*15, 15, 15));
	b1 = new BlueBird(GameObjectName::GameObject_Bird, pBirdSprite, pBirdCircle, pWorld,30);

	b1->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_BlueBird2);
	b1->bState = NORMAL2;

	b1->pBody->SetLinearVelocity(this->pBody->GetLinearVelocity());
	b2Vec2 tmp(-offset.x, offset.y);
	tmp *= 5;
	b1->pBody->ApplyLinearImpulse( tmp, pBody->GetWorldCenter(), true );

	pBirdSprite = new GameSprite( SpriteBatchName::SpriteBatch_Moving,SpriteName::Sprite_Bird, ImageName::Image_BlueBird, Rect(pos.x+offset.x*15, pos.y-offset.y*15, 15, 15) );
	pBirdCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Color(Yellow), Rect(pos.x+offset.x*15, pos.y-offset.y*15, 15, 15));
	b2 = new BlueBird(GameObjectName::GameObject_Bird, pBirdSprite, pBirdCircle, pWorld,30);

	b2->bState = NORMAL2;
	b2->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_BlueBird2);

	b2->pBody->SetLinearVelocity(this->pBody->GetLinearVelocity());
	b2Vec2 tmp2(offset.x, -offset.y);
	tmp2 *= 5;
	tmp+=pBody->GetLinearVelocity();
	

	b2->pBody->ApplyLinearImpulse( tmp2, pBody->GetWorldCenter(), true );

}

std::list <GameSprite*> BlueBird::getTrail()
{
	std::list<GameSprite*> tmp;
	if (b1)
	{
		tmp = b1->getTrail();
		while (!tmp.empty())
		{
			smokeTrail.push_back(tmp.front());
			tmp.pop_front();
		}
	}
	if (b2)
	{
		tmp = b2->getTrail();
		while (!tmp.empty())
		{
			smokeTrail.push_back(tmp.front());
			tmp.pop_front();
		}
	}
	return smokeTrail;
}

void BlueBird::launch()
{
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_BlueBird1);
	launchSound = Sound::getSoundEngine()->play2D("blue flying.mp3", false, false, true);

}

void BlueBird::hit()
{
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_BlueBird3);
	launchSound = Sound::getSoundEngine()->play2D("blue collision a1.mp3", false, false, true);
}

BlueBird::~BlueBird()
{
	if (b1&&b2)
	{
		//b1->markForDelete();
		b1->pGameSprite->display = false;
		b1->pCircleSprite->display = false;
		b1->pBody->SetActive(false);
		//b2->markForDelete();
		b2->pGameSprite->display = false;
		b2->pCircleSprite->display = false;
		b2->pBody->SetActive(false);
	}
}