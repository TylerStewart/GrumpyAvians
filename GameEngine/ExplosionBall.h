#ifndef GAME_OBJECT_EXPLOSION_BALL_H
#define GAME_OBJECT_EXPLOSION_BALL_H

#include "GameSprite.h"
#include "CircleSprite.h"
#include "Box2D/Common/b2Math.h"
#include "GameObjectBird.h"
class b2Body;


class ExplosionBall: public GameObjectBird
{
public:
	
	ExplosionBall( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite, b2World* pWorld, float density);
	void onMouseAction() override;
	virtual void launch() override;
	virtual void hit() override;
	void update2() override;
	void trail();
	CircleSprite	*pCircleSprite;
	int cnt;
	bool nextStage;
	void takeDamage(float d);

};

#endif