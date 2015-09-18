#ifndef ANGRY_CONTACT_LISTENER_H
#define ANGRY_CONTACT_LISTENER_H

#include "Box2D.h"
#include "PixelToMeter.h"

#include "AzulStopWatch.h"

#include "AngryContactListener.h"


extern AzulStopWatch stopWatch;
extern AzulStopWatch totalWatch;


class AngryContactListener : public b2ContactListener
{

public:

	AngryContactListener()
	{
	}

	void BeginContact(b2Contact* contact)
	{ /* handle begin event */ 
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		GameObject *gObjA = (GameObject *)fixtureA->GetUserData();
		GameObject *gObjB = (GameObject *)fixtureB->GetUserData();
		if( gObjA->gameObjName == GameObjectName::GameObject_Bird&&gObjB->gameObjName == GameObjectName::GameObject_Block)
		{
			GameObjectBird *pBird = (GameObjectBird * )gObjA;
			pBird->bState = NORMAL3;
			pBird->hit();

		}
		if( gObjB->gameObjName == GameObjectName::GameObject_Bird&&gObjA->gameObjName == GameObjectName::GameObject_Block)
		{
			GameObjectBird *pBird = (GameObjectBird * )gObjB;
			pBird->bState = NORMAL3;
			pBird->hit();
		}
	
	}

	void EndContact(b2Contact* )
	{ /* handle end event */ 
	}

		void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse )
	{ /* handle post-solve event */

		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		GameObject *gObjA = (GameObject *)fixtureA->GetUserData();
		GameObject *gObjB = (GameObject *)fixtureB->GetUserData();

		gObjA;
		gObjB;

		b2WorldManifold worldManifold;
		contact->GetWorldManifold( &worldManifold );

		float impTotal=0;
		int numImpulse = impulse->count;
	    //assert( numImpulse == numPoints);
		for( int i = 0; i< numImpulse; i++ )
		{
			impTotal+=impulse->normalImpulses[i];
		}
		
		
		
		if( gObjA->gameObjName == GameObjectName::GameObject_Block )
		{
			GameObjectBlock *pBlock = (GameObjectBlock * )gObjA;
			ImageName::Name currName;
			currName = pBlock->pGameSprite->spriteModel->pImage->imageName;  
			if (impTotal>7)	
				pBlock->takeDamage(impTotal);
		
			ImageName::Name newName;
			newName = pBlock->getNextImageName( currName );

			gObjA->pGameSprite->spriteModel->SwapImage(newName);
		}

		if( gObjB->gameObjName == GameObjectName::GameObject_Block )
		{
			GameObjectBlock *pBlock = (GameObjectBlock * )gObjB;
			ImageName::Name currName;
			currName= pBlock->pGameSprite->spriteModel->pImage->imageName;  
			if (impTotal>7)	
				pBlock->takeDamage(impTotal);
		
			ImageName::Name newName;
			newName = pBlock->getNextImageName( currName );

			gObjB->pGameSprite->spriteModel->SwapImage(newName);
		}

		if( gObjA->gameObjName == GameObjectName::GameObject_Pig )
		{
			GameObjectBird *pPig = (GameObjectBird * )gObjA;
			ImageName::Name currName;
			currName = pPig->pGameSprite->spriteModel->pImage->imageName;  
			if (impTotal>5)	
			pPig->takeDamage(impTotal);
		
			ImageName::Name newName;
			newName = pPig->getNextImageName( currName );

			gObjA->pGameSprite->spriteModel->SwapImage(newName);
		}

		if( gObjB->gameObjName == GameObjectName::GameObject_Pig )
		{
			GameObjectBird *pPig = (GameObjectBird * )gObjB;
			ImageName::Name currName;
			currName = pPig->pGameSprite->spriteModel->pImage->imageName;  
			if (impTotal>5)	
			pPig->takeDamage(impTotal);
		
			ImageName::Name newName;
			newName = pPig->getNextImageName( currName );

			gObjB->pGameSprite->spriteModel->SwapImage(newName);
		}

	}
	
};

#endif