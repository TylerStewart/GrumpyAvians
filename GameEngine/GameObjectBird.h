#ifndef GAME_OBJECT_BIRD_H
#define GAME_OBJECT_BIRD_H

#include "GameSprite.h"
#include "CircleSprite.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D.h"
#include <stdio.h>
#include <list>
#include "irrKlang.h"
#include "Sound.h"
using namespace irrklang;

class b2Body;

enum BirdState
{
	OTHER,
	GROUND,
	SLING,
	NORMAL1,
	NORMAL2,
	NORMAL3,
	MOVING
};

class GameObjectBird: public GameObject
{
public:
	
	GameObjectBird( GameObjectName::Name name, GameSprite *pGameSprite, CircleSprite *pDebugSprite, b2World*  pWorld , float density);
	void update( b2Vec2 posInMeters, float angleInRadians ) override;
	virtual ~GameObjectBird();
	CircleSprite	*pCircleSprite;
	BirdState bState;
	virtual void onMouseAction();
	virtual void launch();
	virtual void hit();
	virtual void trail();
	virtual void update2();
	ISound* launchSound;
	ISound* hitSound;

	ImageName::Name getNextImageName( ImageName::Name currName );
	ImageName::Name original;
	int stage;
	float perStage;
	float damage;
	bool nextStage;
	void takeDamage(float d);
	b2Vec2 prev;
	b2Vec2 dir;
	float lastx;
	float lasty;
	float dist;
	int smokenum;
	virtual std::list <GameSprite*> getTrail();
	std::list <GameSprite*> smokeTrail;
};

#endif