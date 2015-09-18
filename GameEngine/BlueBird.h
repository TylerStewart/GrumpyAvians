#ifndef GAME_OBJECT_BLUE_BIRD_H
#define GAME_OBJECT_BLUE_BIRD_H

#include "GameSprite.h"
#include "CircleSprite.h"
#include "Box2D/Common/b2Math.h"
#include "GameObjectBird.h"


class b2Body;


class BlueBird: public GameObjectBird
{
public:
	
	BlueBird( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite, b2World* pWorld, float density);
	void onMouseAction() override;
	virtual void launch() override;
	virtual void hit() override;
	virtual std::list<GameSprite*> getTrail() override;
	virtual ~BlueBird();
	CircleSprite	*pCircleSprite;
	void setWorld(b2World *world);
	b2World	*pWorld;
	bool nextStage;
	void takeDamage(float d);
	GameObjectBird* b1;
	GameObjectBird* b2;
};

#endif