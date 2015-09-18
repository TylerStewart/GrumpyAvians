
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "GameObjectBird.h"





float threshold = 30;

GameObjectBird::GameObjectBird( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite, b2World* pWorld, float density)
{
	this->gameObjName = name;
	this->pGameSprite = gSprite;
	this->pCircleSprite = dSprite;
	this->pBody = 0;

	this->pos.x = dSprite->posX;
	this->pos.y = dSprite->posY;
	this->angle = dSprite->angle;
	bState=NORMAL1;
	damage = 0;
	stage = 0;
	prev = pos;

	b2BodyDef RedBirdDef;
	RedBirdDef.type = b2_dynamicBody;
	RedBirdDef.angularDamping = 0.99f;
	RedBirdDef.position.Set( PixelToMeter(this->pCircleSprite->posX), PixelToMeter(this->pCircleSprite->posY) );
	RedBirdDef.angle = 	this->angle;
	b2Body *pRedBirdBody = pWorld->CreateBody(&RedBirdDef);
		
	b2CircleShape RedBirdCircle;
	RedBirdCircle.m_radius = PixelToMeter(this->pCircleSprite->origWidth * 0.5f);
		
	b2FixtureDef RedBirdFixtureDef;
	
	RedBirdFixtureDef.shape = &RedBirdCircle;
	RedBirdFixtureDef.density = density;
	RedBirdFixtureDef.friction = 0.5f;
	RedBirdFixtureDef.restitution = 0.30f;
	RedBirdFixtureDef.userData = this;
	pRedBirdBody->CreateFixture( &RedBirdFixtureDef);

	pRedBirdBody->SetUserData( this);
	this->pBody = pRedBirdBody;
	this->bState = GROUND;
	dist = 0;
	smokenum = 0;
	
}

void GameObjectBird::takeDamage(float d)//because my pigs are secretly birds.  Its bad, I know.  
{
	if (!damageActive)
		return;
	if (stage>3)
	{
		markForDelete();
		return;
	}
	damage+=d;;
	
	if (damage>=perStage)
	{
		damage = damage-perStage;
		stage+=1;
		takeDamage(damage);
		nextStage=true;
	}
}

void GameObjectBird::onMouseAction()
{
	
}

void GameObjectBird::launch()
{
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_RedBird1);
	launchSound = Sound::getSoundEngine()->play2D("red flying.mp3", false, false, true);
}

void GameObjectBird::hit()
{
	this->pGameSprite->spriteModel->SwapImage(ImageName::Name::Image_RedBird3);
	launchSound = Sound::getSoundEngine()->play2D("red collision a1.mp3", false, false, true);
}

void GameObjectBird::trail()
{
	if (this->bState == NORMAL1||this->bState == NORMAL2)
	{
		GameSprite* g;
		if (smokenum == 0 )
			g = new GameSprite(SpriteBatchName::SpriteBatch_Background2, SpriteName::Sprite_Smoke, ImageName::Image_Smoke,Rect(this->pos.x, this->pos.y,6, 6) );
		else if (smokenum == 1 )
			g = new GameSprite(SpriteBatchName::SpriteBatch_Background2, SpriteName::Sprite_Smoke, ImageName::Image_Smoke,Rect(this->pos.x, this->pos.y,8, 8) );
		else
			g = new GameSprite(SpriteBatchName::SpriteBatch_Background2, SpriteName::Sprite_Smoke, ImageName::Image_Smoke,Rect(this->pos.x, this->pos.y,11, 11) );
		dist = 0;
		smokenum++;
		smokeTrail.push_front(g);
		if (smokenum>2)
			smokenum = 0;
	}
}


void GameObjectBird::update2()
{

}

std::list <GameSprite*> GameObjectBird::getTrail()
{
	return smokeTrail;
}



void GameObjectBird::update( b2Vec2 posInMeters, float angleInRadians ) 
{
	if (active)
	{
			// updates position and angle from physics update
		this->pos.x = MeterToPixel( posInMeters.x );
		this->pos.y = MeterToPixel( posInMeters.y );
		this->angle = angleInRadians;
		dir = pos-prev;
		b2Fixture *pFix = this->pBody->GetFixtureList();

		while( pFix != 0 )
		{
			GameObject *pGObj = (GameObject *)pFix->GetUserData();

			// push the values to the GameSprite
			pGObj->pGameSprite->posX = pos.x;
			pGObj->pGameSprite->posY = pos.y;
			pGObj->pGameSprite->angle = angle;

			// push the values to the DebugSprite
			this->pCircleSprite->posX  = pos.x;
			this->pCircleSprite->posY = pos.y;
			this->pCircleSprite->angle = angle;

			pFix = pFix->GetNext();
		}
		prev = pos;
	}
	b2Vec2 tmp (pos.x-lastx, pos.y-lasty);
	dist+=tmp.Length();
	if (dist>threshold)
		trail();
	lastx = pos.x;
	lasty=pos.y;
	update2();
}

GameObjectBird::~GameObjectBird()
{
}

