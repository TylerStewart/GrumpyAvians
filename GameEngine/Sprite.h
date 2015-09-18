#ifndef SPRITE_H
#define SPRITE_H

#include "GraphicsObject.h"
#include "EnumName.h"

class Sprite : public GraphicsObject
{
public:

	void Sprite::Draw()
	{
		transform();
		setRenderState();
		draw();
	}

	Sprite()
	{
		this->display = true;
		this->spriteBatchName = SpriteBatchName::Not_Initialized;
	}

	void update()
	{
		this->transform();
	}

	// These are pure virtual, needed to be defined by the derived class
	virtual void transform( void ) = 0;   
	virtual void draw(void) = 0;
	virtual void setRenderState(void) = 0;
	
	
	bool display;
	SpriteBatchName::Name spriteBatchName;
	void enable()
	{
		this->display = true;
	}
	void disable()
	{
		this->display = false;
	}

private:


};

#endif