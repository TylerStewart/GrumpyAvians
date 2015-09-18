#ifndef GAME_OBJECT_YELLOW_BIRD_H
#define GAME_OBJECT_YELLOW_BIRD_H

#include "GameSprite.h"
#include "CircleSprite.h"
#include "Box2D/Common/b2Math.h"
#include "GameObjectBird.h"
class b2Body;


class YellowBird: public GameObjectBird
{
public:
	
	YellowBird( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite, b2World* pWorld, float density);
	void onMouseAction() override;
	virtual void launch() override;
	virtual void hit() override;
	CircleSprite	*pCircleSprite;

	bool nextStage;
	void takeDamage(float d);

};

#endif