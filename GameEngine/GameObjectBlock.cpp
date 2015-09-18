
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "GameObjectBlock.h"
#include "EnumName.h"
#include "SBNode.h"

void GameObjectBlock::takeDamage(float d)
{
	if (!damageActive)
		return;
	if (stage>4)
	{
		hit = Sound::getSoundEngine()->play2D("wood destroyed a1.mp3", false, false, true);
		//this->pBody->SetActive(false);
		this->pBody->SetAwake(false);
		markForDelete();
		return;
	}
	damage+=d;;
	
	if (damage>=perStage)
	{
		hit = Sound::getSoundEngine()->play2D("wood damage a1.mp3", false, false, true);
		damage = damage-perStage;
		stage+=1;
		takeDamage(damage);
		nextStage=true;
	}
}

ImageName::Name GameObjectBlock::getNextImageName( ImageName::Name currName )
{
	if (!nextStage)
		return currName;
	ImageName::Name tmp;
	switch (original)
	{
	case ImageName::woodMiniPlank1:
		switch( stage )
		{
			case 1 :
				tmp = ImageName::woodMiniPlank2;
				break;

			case 2 :
				tmp = ImageName::woodMiniPlank3;
				break;

			case 3 :
				tmp = ImageName::woodMiniPlank4;
				break;

			case 4 :
				tmp = ImageName::woodMiniPlank4;
				break;

			default:
			
				tmp = ImageName::woodMiniPlank4;
		}break;
		case ImageName::woodPlankShort1:
			switch( stage )
			{
				case 1 :
					tmp = ImageName::woodPlankShort2;
					break;

				case 2 :
					tmp = ImageName::woodPlankShort3;
					break;

				case 3 :
					tmp = ImageName::woodPlankShort4;
					break;

				case 4 :
					tmp = ImageName::woodPlankShort4;
					break;

				default:
					
					tmp = ImageName::woodPlankShort4;
			}break;
			case ImageName::woodPlankMed1:
			switch( stage )
			{
				case 1 :
					tmp = ImageName::woodPlankMed2;
					break;

				case 2 :
					tmp = ImageName::woodPlankMed3;
					break;

				case 3:
					tmp = ImageName::woodPlankMed4;
					break;

				case 4 :
					tmp = ImageName::woodPlankMed4;
					break;

				default:
					
					tmp = ImageName::woodPlankShort4;
			}break;
		case ImageName::woodBrick1:
		switch( stage )
		{
			case 1 :
				tmp = ImageName::woodBrick2;
				break;

			case 2 :
				tmp = ImageName::woodBrick3;
				break;

			case 3 :
				tmp = ImageName::woodBrick4;
				break;

			case 4 :
				tmp = ImageName::woodBrick4;
				break;

			default:
			
				tmp = ImageName::woodBrick4;
		}break;

		case ImageName::stoneBrick1:
		switch( stage )
		{
			case 1 :
				tmp = ImageName::stoneBrick2;
				break;

			case 2 :
				tmp = ImageName::stoneBrick3;
				break;

			case 3 :
				tmp = ImageName::stoneBrick4;
				break;

			case 4 :
				tmp = ImageName::stoneBrick4;
				break;

			default:
			
				tmp = ImageName::stoneBrick4;
		}break;

		case ImageName::woodHalfBrick1:
		switch( stage )
		{
			case 1 :
				tmp = ImageName::woodHalfBrick2;
				break;

			case 2 :
				tmp = ImageName::woodHalfBrick3;
				break;

			case 3 :
				tmp = ImageName::woodHalfBrick4;
				break;

			case 4 :
				tmp = ImageName::woodHalfBrick4;
				break;

			default:
			
				tmp = ImageName::woodHalfBrick4;
		}break;

		case ImageName::glassBrick1:
		switch( stage )
		{
			case 1 :
				tmp = ImageName::glassBrick2;
				break;

			case 2 :
				tmp = ImageName::glassBrick3;
				break;

			case 3 :
				tmp = ImageName::glassBrick4;
				break;

			case 4 :
				tmp = ImageName::glassBrick4;
				break;

			default:
			
				tmp = ImageName::glassBrick4;
		}break;

			case ImageName::glassPlankShort1:
			switch( stage )
			{
				case 1 :
					tmp = ImageName::glassPlankShort2;
					break;

				case 2 :
					tmp = ImageName::glassPlankShort3;
					break;

				case 3 :
					tmp = ImageName::glassPlankShort4;
					break;

				case 4 :
					tmp = ImageName::glassPlankShort4;
					break;

				default:
					
					tmp = ImageName::woodPlankShort4;
			}break;
		default: 
			//assert(0);
			tmp = ImageName::BLANK;
	}

	return tmp;
}

GameObjectBlock::~GameObjectBlock()
{
	SBNode *pSBNode;
	pSBNode = SpriteBatchManager::Find(this->pBoxSprite->spriteBatchName);
	pSBNode->removeSprite( this->pBoxSprite );
}

GameObjectBlock::GameObjectBlock( GameObjectName::Name name, GameSprite *gSprite,  BoxSprite *dSprite, float perstage )
{
	this->gameObjName = name;
	this->pGameSprite = gSprite;
	this->pBoxSprite = dSprite;
	this->pBody = 0;
	
	
	this->pos.x = dSprite->posX;
	this->pos.y = dSprite->posY;
	this->angle = dSprite->angle;
	perStage = perstage;
	damage = 0;
	stage = 0;
	nextStage = false;
	damageActive = false;
}

void GameObjectBlock::setOriginal(ImageName::Name iname)
{
	
	original = iname;
	
}

ImageName::Name GameObjectBlock::returnOriginal()
{
	return (original);
}

void GameObjectBlock::update( b2Vec2 posInMeters, float angleInRadians ) 
{
		// updates position and angle from physics update
	this->pos.x = MeterToPixel( posInMeters.x );
	this->pos.y = MeterToPixel( posInMeters.y );
	this->angle = angleInRadians;
	
	b2Fixture *pFix = this->pBody->GetFixtureList();

	while( pFix != 0 )
	{
		GameObject *pGObj = (GameObject *)pFix->GetUserData();

		// push the values to the GameSprite
		pGObj->pGameSprite->posX = pos.x;
		pGObj->pGameSprite->posY = pos.y;
		pGObj->pGameSprite->angle = angle;

		// push the values to the DebugSprite
		this->pBoxSprite->posX  = pos.x;
		this->pBoxSprite->posY = pos.y;
		this->pBoxSprite->angle = angle;

		pFix = pFix->GetNext();
	}

}