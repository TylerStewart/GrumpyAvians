#ifndef DATA_H
#define DATA_H

#include "Blocks.h"
#include "Pig.h"
#include "Platform.h"

void loadTextures()
{
	TextMan::Load(TextType::Text2D, TextName::Name::Background, "AngryBirdBackground.tga");
	TextMan::Load(TextType::Text2D, TextName::Name::Birds, "unsorted.tga");
	TextMan::Load(TextType::Text2D, TextName::Name::glassBlocks, "glassBlocks.tga");
	TextMan::Load(TextType::Text2D, TextName::Name::woodBlocks, "woodBlocks.tga");
	TextMan::Load(TextType::Text2D, TextName::Name::stoneBlocks, "stoneBlocks.tga");
	TextMan::Load(TextType::Text2D, TextName::Name::woodPlatform, "woodPlatform.tga");
};

void loadImages()
{
	ImageMan::Add(ImageName::Name::Background, TextName::Name::Background, Rect(1280, 864, -1280, -864));
	ImageMan::Add(ImageName::Name::Red, TextName::Name::Birds, Rect(903, 797, 46, 46) );
	ImageMan::Add(ImageName::Name::Pig, TextName::Name::Birds, Rect(297, 356, 100, 99) );
	ImageMan::Add(ImageName::Name::SlingRight, TextName::Name::Birds, Rect(0, 0, 40, 200));
	ImageMan::Add(ImageName::Name::SlingLeft, TextName::Name::Birds, Rect(832, 0, 44, 125));
	ImageMan::Add(ImageName::Name::woodMiniPlank, TextName::Name::woodBlocks, Rect(458, 256, 41, 22));
	ImageMan::Add(ImageName::Name::woodPlankShort, TextName::Name::woodBlocks, Rect(288, 344, 83, 22));
	ImageMan::Add(ImageName::Name::woodPlankMed, TextName::Name::woodBlocks, Rect(288, 257, 168, 20));
	ImageMan::Add(ImageName::Name::woodPlatform, TextName::Name::woodPlatform, Rect(0, 0, 156, 44));
};

void loadSprites()
{
	SpriteMan::Add(SpriteName::Name::Background,	SpriteBatchName::Name::Background, ImageName::Name::Background, Rect(640, 432, 1280, 864));
	SpriteMan::Add(SpriteName::Name::Red,			 SpriteBatchName::Name::Birds, ImageName::Name::Red, Rect(0, 200, 30, 30) );
	SpriteMan::Add(SpriteName::Name::Pig1,			 SpriteBatchName::Name::Birds, ImageName::Name::Pig, Rect(0, 200, 50, 50) );
	SpriteMan::Add(SpriteName::Name::SlingRight,	 SpriteBatchName::Name::Layer1, ImageName::Name::SlingRight, Rect(200, 230, 40, 100) );
	SpriteMan::Add(SpriteName::Name::SlingLeft,		 SpriteBatchName::Name::Layer2, ImageName::Name::SlingLeft, Rect(177, 250, 35, 60) );
	SpriteMan::Add(SpriteName::Name::woodMiniPlank1, SpriteBatchName::Name::Blocks, ImageName::Name::woodMiniPlank, Rect(50, 50, 40, 22));
	SpriteMan::Add(SpriteName::Name::woodMiniPlank2, SpriteBatchName::Name::Blocks, ImageName::Name::woodMiniPlank, Rect(50, 80, 40, 22));
	SpriteMan::Add(SpriteName::Name::woodMiniPlank3, SpriteBatchName::Name::Blocks, ImageName::Name::woodMiniPlank, Rect(50, 100, 40, 22));
	SpriteMan::Add(SpriteName::Name::woodMiniPlank4, SpriteBatchName::Name::Blocks, ImageName::Name::woodMiniPlank, Rect(50, 100, 40, 22));
	SpriteMan::Add(SpriteName::Name::woodPlankShort1,SpriteBatchName::Name::Blocks, ImageName::Name::woodPlankShort, Rect(50, 50, 83, 22));
	SpriteMan::Add(SpriteName::Name::woodPlankShort2,SpriteBatchName::Name::Blocks, ImageName::Name::woodPlankShort, Rect(50, 80, 83, 22));
	SpriteMan::Add(SpriteName::Name::woodPlankShort3,SpriteBatchName::Name::Blocks, ImageName::Name::woodPlankShort, Rect(50, 100, 83, 22));
	SpriteMan::Add(SpriteName::Name::woodPlankMed1,	 SpriteBatchName::Name::Blocks, ImageName::Name::woodPlankMed, Rect(0, 0, 168, 20));
	SpriteMan::Add(SpriteName::Name::woodPlankMed2,	 SpriteBatchName::Name::Blocks, ImageName::Name::woodPlankMed, Rect(0, 0, 168, 20));
	SpriteMan::Add(SpriteName::Name::woodPlankMed3,	 SpriteBatchName::Name::Blocks, ImageName::Name::woodPlankMed, Rect(0, 0, 168, 20));
	SpriteMan::Add(SpriteName::Name::woodPlankMed4,	 SpriteBatchName::Name::Blocks, ImageName::Name::woodPlankMed, Rect(0, 0, 168, 20));
	SpriteMan::Add(SpriteName::Name::woodPlankMed5,	 SpriteBatchName::Name::Blocks, ImageName::Name::woodPlankMed, Rect(0, 0, 168, 20));
	SpriteMan::Add(SpriteName::Name::woodPlatform1,	 SpriteBatchName::Name::Blocks, ImageName::Name::woodPlatform, Rect(700, 300, 200, 44));
	SpriteMan::Add(SpriteName::Name::woodPlatform2,	 SpriteBatchName::Name::Blocks, ImageName::Name::woodPlatform, Rect(500, 300, 200, 44));
};

void addBatches()
{
	SpriteBatchManager::AddBatch(SpriteBatchName::Name::ColBoxes);
	SpriteBatchManager::AddBatch(SpriteBatchName::Name::Layer2);
	SpriteBatchManager::AddBatch(SpriteBatchName::Name::Birds);
	SpriteBatchManager::AddBatch(SpriteBatchName::Name::Blocks);
	SpriteBatchManager::AddBatch(SpriteBatchName::Name::Layer1);
	SpriteBatchManager::AddBatch(SpriteBatchName::Name::Background);
};

void addBlocks()
{
	new Blocks(GameObjName::Name::miniBlock1, SpriteName::Name::woodMiniPlank1, 1000, 650, b2_pi/2);
	new Blocks(GameObjName::Name::miniBlock2, SpriteName::Name::woodMiniPlank2, 820, 250, b2_pi/2);
	new Blocks(GameObjName::Name::miniBlock3, SpriteName::Name::woodMiniPlank3, 1180, 250, b2_pi/2);
	new Blocks(GameObjName::Name::miniBlock4, SpriteName::Name::woodMiniPlank4, 1000, 450, 0);
	new Blocks(GameObjName::Name::smBlock1, SpriteName::Name::woodPlankShort1, 1000, 600, 0);
	new Blocks(GameObjName::Name::smBlock2, SpriteName::Name::woodPlankShort2, 1000, 250, 0);
	new Blocks(GameObjName::Name::smBlock3, SpriteName::Name::woodPlankShort3, 1000, 300, 0);
	new Blocks(GameObjName::Name::medBlock1, SpriteName::Name::woodPlankMed1, 930, 300, b2_pi/2);
	new Blocks(GameObjName::Name::medBlock2, SpriteName::Name::woodPlankMed2, 1075, 300, b2_pi/2);
	new Blocks(GameObjName::Name::medBlock3, SpriteName::Name::woodPlankMed3, 1000, 400, 0);
	new Blocks(GameObjName::Name::medBlock4, SpriteName::Name::woodPlankMed4, 960, 500, b2_pi/2);
	new Blocks(GameObjName::Name::medBlock5, SpriteName::Name::woodPlankMed5, 1040, 500, b2_pi/2);
	new Platform(GameObjName::Name::woodPlatform1, SpriteName::Name::woodPlatform1, 1100, 200, 0);
	new Platform(GameObjName::Name::woodPlatform2, SpriteName::Name::woodPlatform2, 900, 200, 0);
};

void addPigs()
{
	new Pig(GameObjName::Name::Pig1, SpriteName::Name::Pig1, 1000, 500);

};

#endif