#ifndef GAME_OBJECT_BLOCK_H
#define GAME_OBJECT_BLOCK_H

#include "GameSprite.h"

#include "BoxSprite.h"
#include "Box2D/Common/b2Math.h"
#include "EnumName.h"
#include "irrKlang.h"
#include "Sound.h"
using namespace irrklang;

class b2Body;

class GameObjectBlock: public GameObject
{
public:
	
	GameObjectBlock( GameObjectName::Name name, GameSprite *pGameSprite, BoxSprite *pDebugSprite, float perstage);
	void update( b2Vec2 posInMeters, float angleInRadians ) override;
	void setOriginal(ImageName::Name iname);
	ImageName::Name returnOriginal();
	ImageName::Name getNextImageName( ImageName::Name currName );
	ImageName::Name original;
	BoxSprite	*pBoxSprite;
	int stage;
	float perStage;
	float damage;
	bool nextStage;
	void takeDamage(float d);
	~GameObjectBlock();
	ISound* hit;
	ISound* dest;

};

#endif