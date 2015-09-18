#ifndef GAME_OBJECT_BLACK_BIRD_H
#define GAME_OBJECT_BLACK_BIRD_H

#include "GameSprite.h"
#include "CircleSprite.h"
#include "Box2D/Common/b2Math.h"
#include "GameObjectBird.h"


class b2Body;


class BlackBird: public GameObjectBird
{
public:
	
	BlackBird( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite, b2World* pWorld, float density);
	void onMouseAction() override;
	virtual void launch() override;
	virtual void hit() override;
	void fireParticle(float x, float y);
	void update2() override;
	void Explode();
	virtual ~BlackBird();
	CircleSprite	*pCircleSprite;
	void setWorld(b2World *world);
	b2World	*pWorld;
	bool nextStage;
	void takeDamage(float d);
	GameObjectBird* b1;
	int countdown;
	bool counting;
	//GameObjectBird* b2;
};

#endif