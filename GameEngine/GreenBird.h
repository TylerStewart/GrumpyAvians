#ifndef GAME_OBJECT_GREEN_BIRD_H
#define GAME_OBJECT_GREEN_BIRD_H

#include "GameSprite.h"
#include "CircleSprite.h"
#include "Box2D/Common/b2Math.h"
#include "GameObjectBird.h"
class b2Body;


class GreenBird: public GameObjectBird
{
public:
	
	GreenBird( GameObjectName::Name name, GameSprite *pGameSprite, CircleSprite *pDebugSprite, b2World* pWorld, float density );
	void onMouseAction() override;
	virtual void launch() override;
	virtual void hit() override;
	void update2();
	CircleSprite	*pCircleSprite;
	b2Vec2 boom;
	bool first;
	bool nextStage;
	void takeDamage(float d);
	int boomtimer;
};

#endif