#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "SBNode.h"
	
	extern b2World			*pWorld;
	static int globalIndex = -1;

GameObject::GameObject( )
{

	this->pBody = 0;
	flagForDelete = false;
	damageActive = false;
}

void GameObject::markForDelete()
{
	flagForDelete=true;
}

GameObject::~GameObject()
{
	printf("shoop");
	SBNode *pSBNode;
	pSBNode = SpriteBatchManager::Find(this->pGameSprite->spriteBatchName);
	pSBNode->removeSprite( this->pGameSprite );


	pWorld->DestroyBody(this->pBody);
}








