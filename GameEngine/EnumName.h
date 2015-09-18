
#ifndef ENUM_NAME_H
#define ENUM_NAME_H


struct EnumName
{
	enum Name
	{
		Stubb // needed for overloading
	};

	bool operator == (EnumName tmp )
	{
		return ( this->value == tmp.value);
	}

	int value;
};

struct SpriteBatchName: public EnumName
{
	SpriteBatchName( SpriteBatchName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		SpriteBatch_Stitch = 10000,
		SpriteBatch_Invaders,
		SpriteBatch_Debug,
		SpriteBatch_Blocks,
		SpriteBatch_Background,
		SpriteBatch_Background2,
		SpriteBatch_Foreground,
		SpriteBatch_Moving,
		Not_Initialized
	};
};

struct SpriteName: public EnumName
{
	SpriteName( SpriteName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		Sprite_Stitch_0 = 20000,
		Sprite_Stitch_1,
		Sprite_Alien_Green,
		Sprite_Alien_Blue,
		Sprite_Alien_Red_0,
		Sprite_Alien_Red_1,
		Sprite_SlingShot,
		Sprite_Bird,
		Sprite_Smoke,
		Sprite_Block,
		Sprite_Block2,
		Background,
		Red,
		Pig1,
		SlingRight,
		SlingLeft,
		woodMiniPlank1,
		woodMiniPlank2,
		woodMiniPlank3,
		woodMiniPlank4,
		woodPlankShort1,
		woodPlankShort2,
		woodPlankShort3,
		woodPlankShort4,
		woodPlankMed1,
		woodPlankMed2,
		woodPlankMed3,
		woodPlankMed4,
		woodPlankMed5,
		Sprite_BackgroundBackGrass,
		Sprite_BackgroundTrees,
		Sprite_BackgroundClouds,
		Sprite_GLASS_Block,
		Sprite_GLASS_Block2,
		Sprite_BackgroundFrontGrass,
		Sprite_Bang,

		Sprite_Box_Bird,
		Sprite_Box_Block,
		Sprite_Box_Block2,

		Sprite_Box_GLASS_Block,
		Sprite_Box_GLASS_Block2,

		Sprite_Circle,
		Sprite_Poly,

		Not_Initialized
	};
};

struct ImageName: public EnumName
{
	ImageName( ImageName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		Image_Alien_Small = 30000,
		Image_Alien_Medium,
		Image_Alien_Large,
		Image_Stitch,
		Image_Long_Wood_Block,
		Image_Med_Wood_Block,
		Image_Wood_Block,
		Image_Small_Wood_Block,
		Image_Glass_Block,
		Image_RedBird,
		Image_RedBird1,
		Image_RedBird2,
		Image_RedBird3,
		Image_YellowBird,
		Image_YellowBird1,
		Image_YellowBird2,
		Image_YellowBird3,
		Image_GreenBird,
		Image_GreenBird1,
		Image_GreenBird2,
		Image_GreenBird3,
		Image_BlueBird,
		Image_BlueBird1,
		Image_BlueBird2,
		Image_BlueBird3,
		Image_WhiteBird,
		Image_WhiteBird1,
		Image_WhiteBird2,
		Image_WhiteBird3,
		Image_BlackBird1,
		Image_BlackBird2,
		Image_BlackBird3,
		Image_BlackBird,
		Image_Egg,
		Image_Bang,
		Image_Smoke,
		Background,
		Image_BackgroundBackGrass,
		Image_BackgroundTrees,
		Image_BackgroundClouds,
		Image_BackgroundFrontGrass,
		woodMiniPlank1,
		woodMiniPlank2,
		woodMiniPlank3,
		woodMiniPlank4,
		woodPlankShort1,
		woodPlankShort2,
		woodPlankShort3,
		woodPlankShort4,
		woodPlankMed1,
		woodPlankMed2,
		woodPlankMed3,
		woodPlankMed4,
		woodPlankMed5,
		woodTriangle1,
		woodTriangle2,
		woodTriangle3,
		woodTriangle4,
		glassPlankShort1,
		glassPlankShort2,
		glassPlankShort3,
		glassPlankShort4,
		stoneBrick1,
		stoneBrick2,
		stoneBrick3,
		stoneBrick4,
		glassBrick1,
		glassBrick2,
		glassBrick3,
		glassBrick4,
		woodBrick1,
		woodBrick2,
		woodBrick3,
		woodBrick4,
		woodHalfBrick1,
		woodHalfBrick2,
		woodHalfBrick3,
		woodHalfBrick4,
		BLANK,
		Pig1,
		Pig2,
		Pig3,
		Pig4,
		HelmetPig1,
		HelmetPig2,
		HelmetPig3,
		SlingRight,
		SlingLeft,
		woodMiniPlank,
		woodPlankShort,
		woodPlankMed,
		woodPlatform,
		Not_Initialized,
	};
};

struct TextName: public EnumName
{
	TextName( TextName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		Texture_SpaceInvaders = 40000,
		Texture_Stitch,
		Texture_Stones,
		Texture_Wood_Blocks,
		Texture_Glass_Blocks,
		Texture_Stone_Blocks,
		Texture_Background,
		Birds,
		Background,
		woodPlatform,
		woodBlocks,
		stoneBlocks,
		Not_Initialized
	};
};



struct GameObjectName: public EnumName
{
	GameObjectName( GameObjectName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		GameObject_Block = 50000,
		GameObject_Ground,
		GameObject_Block2,
		GameObject_Bird,
		GameObject_Glass_Block,
		GameObject_Glass_Block2,
		GameObject_Pig,
		miniBlock1,
		miniBlock2,
		miniBlock3,
		miniBLock4,
		Not_Initialized
	};
};

#endif