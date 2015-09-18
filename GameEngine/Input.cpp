#include <string>
#include "AzulCore.h"
#include "Input.h"
#include "GameObject.h"
#include "Box2D.h"
#include "PixelToMeter.h"


static float slingX = 90;
static float slingY = 210;

enum PositionState
{
	INSIDE,
	OUTSIDE,
	UNKNOWN
};

enum MouseState
{
	RIGHT = 0x1,
	LEFT  = 0x2,
	NONE = 0
};


void MouseTest( GLFWwindow* window, GameObjectBird *pBird, ScreenLine* pLine1, ScreenLine* pLine2, std::list<GameObject *>  gameObjectList  )
{

	// Quick and dirty test, if these work the rest do.
	// --> try move the mouse inside the window, click right, click left
	if (!pBird)
		return;
	
	if (pBird->bState==SLING)
	{
		pBird->pBody->SetActive(false);
		b2Vec2 newPos( PixelToMeter((float)slingX), PixelToMeter((float)slingY) );
		pBird->pBody->SetTransform( newPos, 0.0f );
	}

	double xpos;
	double ypos;

	static float lastXPos;
	static float lastYPos;
	// get mouse position
	glfwGetCursorPos( window, &xpos, &ypos);
	Camera *pCam = Camera::Instance();
	pCam;
	// correct for origin
	double t = ypos / 600.0;
	ypos = 600.0 + t * (-600.0);


	MouseState			mState = NONE;
	PositionState		pState = UNKNOWN;

	GameObject* b = pBird;
	Matrix viewMatrix = pCam->getViewMatrix();
	Matrix projMatrix = pCam->getProjMatrix();
	Matrix worldMatrix = b->pGameSprite->returnWorld();
	Vect vout = Vect(0.0f,0.0f,0.0f) * worldMatrix * viewMatrix * projMatrix; 
	float zoom = vout[w];
	
	vout[x] = vout[x]/vout[w];
	vout[y] = vout[y]/vout[w];

	float X = (vout[x]+1.0f)*(pCam->viewport_width/2.0f);
	float Y= (vout[y]+1.0f)*(pCam->viewport_height/2.0f);

	Vect birdPos(pBird->pos.x, pBird->pos.y,0.0f);
	Vect mousePos((float ) xpos,(float ) ypos, 0.0f);
	
	Vect local( X, Y, 0.0f);
	Vect Dist = mousePos - local;
	
	if ( Dist.mag() < (10.0f / zoom) )
	{
		pState = INSIDE;
	}
	else
	{
		pState = OUTSIDE;
	}
	//printf("%f - %f", Dist[x],Dist[y] );
	//printf("  |  %f - %f", X, Y );
	//xpos = xpos + Dist[x]*zoom;
	//ypos = ypos + Dist[y]*zoom;
	//printf("%f - %f ",xpos, ypos);
	mState = NONE;
	if( glfwGetMouseButton (window, GLFW_MOUSE_BUTTON_RIGHT ) == GLFW_PRESS)
	{
		mState = RIGHT;
	}

	if( glfwGetMouseButton (window, GLFW_MOUSE_BUTTON_LEFT ) == GLFW_PRESS)
	{
		
		mState = LEFT;
	}

	if (mState == LEFT && pBird->bState == NORMAL1)
	{
		pBird->bState = NORMAL2;
		pBird->onMouseAction();
		
	}

// Enter MOVING state
	if( mState == LEFT && pState == INSIDE)
	{
		;
		pBird->bState = MOVING;
		pBird->pBody->SetActive(false);
	}
	
	// small sublty here, once moving, left dictates mode
	if ( pBird->bState == MOVING)
	{
		if( mState == LEFT )//this drags the bird around
		{
			/*b2Vec2 newPos( PixelToMeter((float)xpos), PixelToMeter((float)ypos) );
			pBird->pBody->SetTransform( newPos, 0.0f );
			
			pLine1->posB=B;
			pLine2->posB=B;*/
			b2Vec2 slingPos(PixelToMeter((float)slingX), PixelToMeter((float)slingY));
			b2Vec2 newPos(PixelToMeter((float)pBird->pos.x+Dist[x]*zoom), PixelToMeter((float)pBird->pos.y+Dist[y]*zoom));
			
			b2Vec2 check(PixelToMeter((float)pBird->pos.x+Dist[x]*zoom-slingX), PixelToMeter((float)pBird->pos.y+Dist[y]*zoom - slingY));
			if (check.Length() > 2)
			{
				check.Normalize();
				newPos = slingPos + 2*check;
			}
			else
			{
				newPos.Set( PixelToMeter((float)pBird->pos.x+Dist[x]*zoom), PixelToMeter((float)pBird->pos.y+Dist[y]*zoom) );
			}
			//printf("%f - %f ",newPos.x, newPos.y);
			pBird->pBody->SetTransform( newPos, 0.0f );
			Vect2D B(MeterToPixel((float)newPos.x), MeterToPixel((float)newPos.y));
			pLine1->posB=B;
			pLine2->posB=B;	
		}
		else//this fires bird from the slingshot
		{	
			
			b2Vec2 slingshot(PixelToMeter(slingX-pBird->pos.x), PixelToMeter(slingY-pBird->pos.y));
			pBird->bState = NORMAL1;
			pBird->pBody->SetActive(true);
			float32 mag = slingshot.Length();
			if (mag>2)
				mag=2;
			slingshot.Normalize();
			if (pBird->pBody->GetMass()<10)
				mag*=20;
			else
				mag*=200;
			b2Vec2 vel;
			vel = mag * slingshot;
			pBird->pBody->ApplyLinearImpulse( vel, pBird->pBody->GetWorldCenter(), true );
			pBird->pBody->SetActive(true);
			Vect2D B(slingX, slingY) ;
			pLine1->posB=B;
			pLine2->posB=B;
			pBird->launch();
			AzulCore::clearTrails();
			std::list< GameObject *>::iterator it=gameObjectList.begin();
			while( it!=gameObjectList.end() )
			{
				GameObject *pGameObj = *it++;
				
				pGameObj->damageActive=true;
			}
		}
	}
	if (pBird->bState==SLING)
	{
		pBird->pBody->SetActive(false);
		b2Vec2 newPos( PixelToMeter((float)slingX), PixelToMeter((float)slingY) );
		pBird->pBody->SetTransform( newPos, 0.0f );
	}

	if (pBird->bState==SLING||pBird->bState==MOVING)
	{
		AzulCore::setTargetAndSpeed((slingX), (slingY), -0.2f,0.01f);
	}
	else 
	{
		AzulCore::setTargetAndSpeed(pBird->pos.x, pBird->pos.y, 0.1f,10.0f);
	}
		
}


void KeyboardTest( GLFWwindow* window, GameObjectBird* pBird)
{
	pBird;
	window;

}
