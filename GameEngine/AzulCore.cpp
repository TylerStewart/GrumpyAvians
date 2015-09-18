#include <Windows.h>
#include <stdio.h>
#include <list>
#include <string>
#include <iostream>
#include <stack>
#include "AZULCore.h"

#include "TextMan.h"
#include "EnumName.h"
#include "Rect.h"
#include "ImageMan.h"
#include "Image.h"
#include "SpriteBatchManager.h"
#include "SpriteBatch.h"
#include "BoxModel.h"
#include "BoxSprite.h"
#include "CircleModel.h"
#include "CircleSprite.h"
#include "PolyModel.h"
#include "PolySprite.h"
#include "AzulStopWatch.h"
#include "Input.h"
#include "Box2D.h"
#include "PixelToMeter.h"
#include "GameObject.h"
#include "GameObjectBird.h"
#include "GameObjectBlock.h"
#include "AngryContactListener.h"
#include "Color.h"
#include "ScreenLine.h"
#include "YellowBird.h"
#include "WhiteBird.h"
#include "GreenBird.h"
#include "BlueBird.h"
#include "BlackBird.h"
#include "Sound.h"
#include "Audio/include/irrKlang.h"
using namespace irrklang;



AzulStopWatch stopWatch;
AzulStopWatch totalWatch;
GLShaderManager	shaderManager;

GameSprite		*pBackGroundClouds = 0;
GameSprite		*pBackGroundTrees = 0;
GameSprite		*pBackGroundGrass = 0;
GameSprite		*pForeGroundGrass = 0;
GameSprite		*pSlingLeft = 0;
GameSprite		*pSlingRight = 0;

GameSprite		*pBang = 0;
b2World			*pWorld;
GameObjectBird	*pBird;
GameObjectBird	*pPig;
ScreenLine		*pLine1;
ScreenLine		*pLine2;

std::list<GameObject *>  gameObjectList;
std::stack<GameObjectBird *>  birds;
std::list <GameSprite*> smokeTrailLast;
float statCount = 0;

ISound* music;
ISound* deleteBird;

Vect cameraTarget;
float camSpeed;

int level = 1;//Loads 1-1 by default, Change this to 9 to load 1-9



//-----------------------------------------------------------------------------
//  AzulCore::AzulCore()
//		Game Engine Constructor
//-----------------------------------------------------------------------------
AzulCore::AzulCore()
{
	Sound::getSoundEngine();
	joystickActive = false;
	printf("createGraphicsWindows()\n");

	// create graphics windows with defaults
	char title[256];
	sprintf_s(title,"%s\n",MONKEY);
	window = createGraphicsWindow(title, 800 , 600);

	// inputs creation
	initInputInterface(window, joystickActive);
}

void loadTextures()
{
	TextMan::Load(TextType::Text2D, TextName::Texture_Wood_Blocks, "woodBlocks.tga" );
	//TextMan::Load(TextType::Text2D, TextName::Birds, "unsorted.tga");

	//TextMan::Load(TextType::Text2D, TextName::Name::Background, "AngryBirdBackground.tga");
	TextMan::Load(TextType::Text2D, TextName::woodBlocks, "woodBlocks.tga" );
	TextMan::Load(TextType::Text2D, TextName::stoneBlocks, "stoneBlocks.tga" );
	TextMan::Load(TextType::Text2D, TextName::Birds, "unsorted.tga");
	TextMan::Load(TextType::Text2D, TextName::Name::Texture_Glass_Blocks, "glassBlocks.tga");
	TextMan::Load(TextType::Text2D, TextName::Name::Texture_Stone_Blocks, "stoneBlocks.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_Background, "TiledBackground.tga");
	//TextMan::Load(TextType::Text2D, TextName::Name::woodPlatform, "woodPlatform.tga");
	//
}

void loadImages()
{
	//Sound::getSoundEngine();
	music = Sound::getSoundEngine()->play2D("ambient_white_dryforest.mp3", true, false, true);
	Sound::getSoundEngine()->setSoundVolume(0.1f);
	ImageMan::Add(ImageName::Image_Long_Wood_Block, TextName::Texture_Wood_Blocks,Rect(288, 257, 168, 20) );
	ImageMan::Add(ImageName::Image_Glass_Block, TextName::Texture_Glass_Blocks,Rect(288, 347, 83, 20) );
	//ImageMan::Add(ImageName::Image_RedBird, TextName::Birds,Rect(903,797,48,48) );
	ImageMan::Add(ImageName::Image_Bang, TextName::Birds,Rect(674, 354, 87,89 ) );
	//ImageMan::Add(ImageName::Image_Bang, TextName::Birds,Rect(674, 354, 87,89 ) );
	ImageMan::Add(ImageName::Name::Background, TextName::Name::Background, Rect(1280, 864, -1280, -864));

	ImageMan::Add(ImageName::Name::Image_RedBird, TextName::Name::Birds, Rect(903, 797, 46, 46) );
	ImageMan::Add(ImageName::Name::Image_RedBird1, TextName::Name::Birds, Rect(956, 844, 50, 45) );
	ImageMan::Add(ImageName::Name::Image_RedBird2, TextName::Name::Birds, Rect(956, 844, 50, 45) );
	ImageMan::Add(ImageName::Name::Image_RedBird3, TextName::Name::Birds, Rect(853, 890, 46, 46) );

	ImageMan::Add(ImageName::Name::Image_WhiteBird, TextName::Name::Birds, Rect(409, 353, 82, 94));
	ImageMan::Add(ImageName::Name::Image_WhiteBird1, TextName::Name::Birds, Rect(494, 352, 85, 93));
	ImageMan::Add(ImageName::Name::Image_WhiteBird2, TextName::Name::Birds, Rect(667, 752, 57, 66));
	ImageMan::Add(ImageName::Name::Image_WhiteBird3, TextName::Name::Birds, Rect(409, 637, 79, 87));

	ImageMan::Add(ImageName::Name::Image_GreenBird, TextName::Name::Birds, Rect(932, 529, 99, 71));
	ImageMan::Add(ImageName::Name::Image_GreenBird1, TextName::Name::Birds, Rect(830, 529, 100, 72));
	ImageMan::Add(ImageName::Name::Image_GreenBird2, TextName::Name::Birds, Rect(955, 155, 85, 96));
	ImageMan::Add(ImageName::Name::Image_GreenBird3, TextName::Name::Birds, Rect(954, 605, 93, 71));

	ImageMan::Add(ImageName::Name::Image_YellowBird, TextName::Name::Birds, Rect(668, 877, 58, 58));
	ImageMan::Add(ImageName::Name::Image_YellowBird1, TextName::Name::Birds, Rect(589, 915, 67, 52));
	ImageMan::Add(ImageName::Name::Image_YellowBird2, TextName::Name::Birds, Rect(865, 746, 67, 50));
	ImageMan::Add(ImageName::Name::Image_YellowBird3, TextName::Name::Birds, Rect(793, 744, 59, 53));

	ImageMan::Add(ImageName::Name::Image_BlueBird, TextName::Name::Birds, Rect(1, 378, 31, 31));
	ImageMan::Add(ImageName::Name::Image_BlueBird1, TextName::Name::Birds, Rect(1, 537, 31, 31));
	ImageMan::Add(ImageName::Name::Image_BlueBird2, TextName::Name::Birds, Rect(1, 537, 31, 31));
	ImageMan::Add(ImageName::Name::Image_BlueBird3, TextName::Name::Birds, Rect(1, 410, 31, 31));

	ImageMan::Add(ImageName::Name::Image_BlackBird, TextName::Name::Birds, Rect(406, 723, 62, 81));
	ImageMan::Add(ImageName::Name::Image_BlackBird1, TextName::Name::Birds, Rect(665, 677, 63, 72));
	ImageMan::Add(ImageName::Name::Image_BlackBird2, TextName::Name::Birds, Rect(648, 445, 61, 81));
	ImageMan::Add(ImageName::Name::Image_BlackBird3, TextName::Name::Birds, Rect(1, 410, 31, 31));

	ImageMan::Add(ImageName::Name::Image_Egg, TextName::Name::Birds, Rect(668, 820, 45, 57));
	ImageMan::Add(ImageName::Name::Image_Smoke, TextName::Name::Birds, Rect(1, 345, 36, 33));
	
	ImageMan::Add(ImageName::Name::SlingRight, TextName::Name::Birds, Rect(0, 0, 40, 200));
	ImageMan::Add(ImageName::Name::SlingLeft, TextName::Name::Birds, Rect(832, 0, 44, 125));

	ImageMan::Add(ImageName::Name::Pig1, TextName::Name::Birds, Rect(297, 356, 100, 99) );
	ImageMan::Add(ImageName::Name::Pig2, TextName::Name::Birds, Rect(611, 255, 98, 98) );
	ImageMan::Add(ImageName::Name::Pig3, TextName::Name::Birds, Rect(712, 256, 100, 97) );

	ImageMan::Add(ImageName::Name::HelmetPig1, TextName::Name::Birds, Rect(490, 444, 93, 85) );
	ImageMan::Add(ImageName::Name::HelmetPig2, TextName::Name::Birds, Rect(490, 529, 93, 85) );
	ImageMan::Add(ImageName::Name::HelmetPig3, TextName::Name::Birds, Rect(490, 869, 93, 85) );

	ImageMan::Add(ImageName::Name::woodTriangle1, TextName::Name::woodBlocks, Rect(169, 1, 80, 80));
	ImageMan::Add(ImageName::Name::woodTriangle2, TextName::Name::woodBlocks, Rect(251, 1, 80, 80));
	ImageMan::Add(ImageName::Name::woodTriangle3, TextName::Name::woodBlocks, Rect(333, 1, 80, 80));
	ImageMan::Add(ImageName::Name::woodTriangle4, TextName::Name::woodBlocks, Rect(415, 1, 80, 80));

	ImageMan::Add(ImageName::Name::woodMiniPlank1, TextName::Name::woodBlocks, Rect(458, 256, 40, 20));
	ImageMan::Add(ImageName::Name::woodMiniPlank2, TextName::Name::woodBlocks,Rect(458, 278, 40, 20) );
	ImageMan::Add(ImageName::Name::woodMiniPlank3, TextName::Name::woodBlocks,Rect(458, 300, 40, 20) );
	ImageMan::Add(ImageName::Name::woodMiniPlank4, TextName::Name::woodBlocks,Rect(458, 322, 40, 20) );

	ImageMan::Add(ImageName::Name::woodPlankShort1, TextName::Name::woodBlocks, Rect(288, 344, 83, 20));
	ImageMan::Add(ImageName::Name::woodPlankShort2, TextName::Name::woodBlocks,Rect(288, 366, 83,20) );
	ImageMan::Add(ImageName::Name::woodPlankShort3, TextName::Name::woodBlocks,Rect(373, 344, 83,20) );
	ImageMan::Add(ImageName::Name::woodPlankShort4, TextName::Name::woodBlocks,Rect(373, 366, 83,20) );

	ImageMan::Add(ImageName::Name::glassPlankShort1, TextName::Name::Texture_Glass_Blocks, Rect(288, 346, 83, 20));
	ImageMan::Add(ImageName::Name::glassPlankShort2, TextName::Name::Texture_Glass_Blocks,Rect(288, 368, 83,20) );
	ImageMan::Add(ImageName::Name::glassPlankShort3, TextName::Name::Texture_Glass_Blocks,Rect(373, 346, 83,20) );
	ImageMan::Add(ImageName::Name::glassPlankShort4, TextName::Name::Texture_Glass_Blocks,Rect(373, 368, 83,20) );

	ImageMan::Add(ImageName::Name::woodPlankMed1, TextName::Name::woodBlocks, Rect(288, 257, 168, 20));
	ImageMan::Add(ImageName::Name::woodPlankMed2, TextName::Name::woodBlocks,Rect(288, 278, 168,20) );
	ImageMan::Add(ImageName::Name::woodPlankMed3, TextName::Name::woodBlocks,Rect(288, 300, 168,20) );
	ImageMan::Add(ImageName::Name::woodPlankMed4, TextName::Name::woodBlocks,Rect(288, 322, 168,20) );

	ImageMan::Add(ImageName::Name::stoneBrick1, TextName::Name::stoneBlocks,Rect(247, 83, 83, 40));
	ImageMan::Add(ImageName::Name::stoneBrick2, TextName::Name::stoneBlocks,Rect(332, 83, 83,40) );
	ImageMan::Add(ImageName::Name::stoneBrick3, TextName::Name::stoneBlocks,Rect(417, 83, 83,40) );
	ImageMan::Add(ImageName::Name::stoneBrick4, TextName::Name::stoneBlocks,Rect(248, 125, 83,40) );

	ImageMan::Add(ImageName::Name::glassBrick1, TextName::Name::Texture_Glass_Blocks,Rect(332, 83, 83,40) );
	ImageMan::Add(ImageName::Name::glassBrick2, TextName::Name::Texture_Glass_Blocks,Rect(417, 83, 83,40) );
	ImageMan::Add(ImageName::Name::glassBrick3, TextName::Name::Texture_Glass_Blocks,Rect(248, 128, 83,40) );
	ImageMan::Add(ImageName::Name::glassBrick4, TextName::Name::Texture_Glass_Blocks,Rect(330, 128, 83, 40));

	ImageMan::Add(ImageName::Name::woodBrick1, TextName::Name::woodBlocks,Rect(247, 83, 83,40));
	ImageMan::Add(ImageName::Name::woodBrick2, TextName::Name::woodBlocks,Rect(332, 83, 83,40) );
	ImageMan::Add(ImageName::Name::woodBrick3, TextName::Name::woodBlocks,Rect(417, 83, 83,40) );
	ImageMan::Add(ImageName::Name::woodBrick4, TextName::Name::woodBlocks,Rect(248, 125, 83,40) );

	ImageMan::Add(ImageName::Name::woodHalfBrick1, TextName::Name::woodBlocks,Rect(2, 338, 40,40));
	ImageMan::Add(ImageName::Name::woodHalfBrick2, TextName::Name::woodBlocks,Rect(86, 338, 40,40) );
	ImageMan::Add(ImageName::Name::woodHalfBrick3, TextName::Name::woodBlocks,Rect(332, 127, 40,40) );
	ImageMan::Add(ImageName::Name::woodHalfBrick4, TextName::Name::woodBlocks,Rect(375, 127, 40,40) );

	ImageMan::Add(ImageName::Name::BLANK, TextName::Name::Birds, Rect(100, 950, 10, 10) );
	ImageMan::Add(ImageName::Image_BackgroundClouds, TextName::Texture_Background,Rect(1283, 950, 1280, 850) );
	ImageMan::Add(ImageName::Image_BackgroundTrees, TextName::Texture_Background,Rect(0, 950, 1280, 850));
	ImageMan::Add(ImageName::Image_BackgroundBackGrass, TextName::Texture_Background,Rect(1283, 0, 1280, 850) );
	ImageMan::Add(ImageName::Image_BackgroundFrontGrass, TextName::Texture_Background,Rect(0, 0, 1280, 850) );
	//ImageMan::Add(ImageName::Name::woodPlatform, TextName::Name::woodPlatform, Rect(0, 0, 156, 44));
	
}

void addBatches()
{
	/*SpriteBatchManager::AddBatch(SpriteBatchName::Name::ColBoxes);
	SpriteBatchManager::AddBatch(SpriteBatchName::Name::Layer2);
	SpriteBatchManager::AddBatch(SpriteBatchName::Name::Birds);
	SpriteBatchManager::AddBatch(SpriteBatchName::Name::Blocks);
	SpriteBatchManager::AddBatch(SpriteBatchName::Name::Layer1);
	SpriteBatchManager::AddBatch(SpriteBatchName::Name::Background);
	//*/
}

void addPigAt(ImageName::Name iname, float x, float y, float size)
{
	if (level == 9)
	{
		x = x+450;
		y = y+97;
	}
	else 
	{
		x= x+450;
		y= y+74;
	}
		
	GameSprite *pPigSprite = new GameSprite( SpriteBatchName::SpriteBatch_Moving,SpriteName::Sprite_Bird, iname, Rect(x, y, size, size) );
	CircleSprite *pPigCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Color(Red), Rect(x, y, size, size));
	                          
	pPig = new GameObjectBird(GameObjectName::GameObject_Pig, pPigSprite, pPigCircle, pWorld, 10.0f );
	pPig->damage = 0;
	pPig->perStage = 70;
	gameObjectList.push_front(pPig);

}//pig is technically bird for now, easier for now

void addHelmetPigAt(ImageName::Name iname, float x, float y, float size)
{
	if (level == 9)
	{
		x = x+450;
		y = y+97;
	}
	else 
	{
		x= x+450;
		y= y+74;
	}
		
	GameSprite *pPigSprite = new GameSprite( SpriteBatchName::SpriteBatch_Moving,SpriteName::Sprite_Bird, iname, Rect(x, y, size, size) );
	CircleSprite *pPigCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Color(Red), Rect(x, y, size, size));
	pPig = new GameObjectBird(GameObjectName::GameObject_Pig, pPigSprite, pPigCircle, pWorld, 10.0f );
	pPig->damage = 0;
	pPig->perStage = 100;                  
	

	gameObjectList.push_front(pPig);

}//pig is technically bird for now, easier for now

void addBackground()
{
	float width = 800;
	float height = 600;
	pBackGroundGrass  = new GameSprite(SpriteBatchName::SpriteBatch_Background, SpriteName::Sprite_BackgroundBackGrass, ImageName::Image_BackgroundBackGrass,Rect(0, height/2, width, height) );
	pBackGroundTrees  = new GameSprite(SpriteBatchName::SpriteBatch_Background, SpriteName::Sprite_BackgroundTrees, ImageName::Image_BackgroundTrees,Rect(0, (height/2)-20, width, height) );
	pBackGroundClouds = new GameSprite(SpriteBatchName::SpriteBatch_Background, SpriteName::Sprite_BackgroundClouds, ImageName::Image_BackgroundClouds, Rect(0, height/2, width, height*2) );
	pForeGroundGrass  = new GameSprite(SpriteBatchName::SpriteBatch_Foreground, SpriteName::Sprite_BackgroundFrontGrass, ImageName::Image_BackgroundFrontGrass,Rect(0, height/2, width, height) );
	pBackGroundGrass  = new GameSprite(SpriteBatchName::SpriteBatch_Background, SpriteName::Sprite_BackgroundBackGrass, ImageName::Image_BackgroundBackGrass,Rect(width, height/2, width, height) );
	pBackGroundTrees  = new GameSprite(SpriteBatchName::SpriteBatch_Background, SpriteName::Sprite_BackgroundTrees, ImageName::Image_BackgroundTrees,Rect(width, (height/2)-20, width, height) );
	pBackGroundClouds = new GameSprite(SpriteBatchName::SpriteBatch_Background, SpriteName::Sprite_BackgroundClouds, ImageName::Image_BackgroundClouds, Rect(width, height/2, width, height*2) );
	pForeGroundGrass  = new GameSprite(SpriteBatchName::SpriteBatch_Foreground, SpriteName::Sprite_BackgroundFrontGrass, ImageName::Image_BackgroundFrontGrass,Rect(width, height/2, width, height) );
	pSlingLeft = new GameSprite(SpriteBatchName::SpriteBatch_Background2, SpriteName::Sprite_SlingShot, ImageName::SlingRight, Rect(100, 173, 32, 116) );
	pSlingRight = new GameSprite(SpriteBatchName::SpriteBatch_Foreground, SpriteName::Sprite_SlingShot, ImageName::SlingLeft, Rect(100-20, 197, 32, 73) );
}

void addBlockAt(ImageName::Name iname, float x, float y, float width, float height, float rot, float perstage)
{
	float xn=x;
	float yn=y;

	if (level == 9)
	{
		x/=2;
		y/=2;
		xn = x+750;
		yn = y+97;
	}
	else 
	{
		xn= x+450;
		yn= y+74;
	}
	GameSprite *pBlockSprite = new GameSprite( SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_Block, iname, Rect(xn, yn, width, height) );
	BoxSprite *pBlockBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Block, 2.0f, Vect(0,0,255,255), pBlockSprite);
	GameObjectBlock *pBlock = new GameObjectBlock(GameObjectName::GameObject_Block , pBlockSprite, pBlockBox, perstage );
	pBlock->angle=rot;
	pBlock->setOriginal(iname);
	
	b2BodyDef BlockDef;
	BlockDef.type = b2_dynamicBody;

	BlockDef.position.Set( PixelToMeter(pBlock->pBoxSprite->posX), PixelToMeter(pBlock->pBoxSprite->posY) );
	BlockDef.angle = 	pBlock->angle;
	b2Body *pBlockBody = pWorld->CreateBody(&BlockDef);
	
	b2PolygonShape BlockBox;
	BlockBox.SetAsBox( PixelToMeter(pBlock->pBoxSprite->origWidth * 0.5f), PixelToMeter(pBlock->pBoxSprite->origHeight * 0.5f) );
	
	b2FixtureDef BlockFixtureDef;
	BlockFixtureDef.shape = &BlockBox;
	BlockFixtureDef.density = 30.50f;
	BlockFixtureDef.friction = 0.8f;
	BlockFixtureDef.restitution = 0.20f;
	BlockFixtureDef.userData = pBlock;
	pBlockBody->CreateFixture( &BlockFixtureDef);
	pBlockBody->SetUserData( pBlock);
	pBlock->pBody = pBlockBody;
	gameObjectList.push_front(pBlock);
}//I am aware of the crumminess of this implementation. 

void addBlocks1()
{
	float wood = 100.0f;
	float glass = 65.0f;
	//float stone = 0;
	//addTriangleAt(ImageName::woodMiniPlank1, 500, 308, 25,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodMiniPlank1, 500, 308, 25,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodMiniPlank1, 410,105,25,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodMiniPlank1, 590,105,25,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodMiniPlank1, 500,205,25,12.5, 0, wood);
	addBlockAt(ImageName::woodPlankShort1, 500,280,42.5,12.5,0, wood);
	addBlockAt(ImageName::woodPlankShort1, 500,105,42.5,12.5, 0, wood);
	addBlockAt(ImageName::woodPlankShort1, 500,155,42.5,12.5, 0, wood);
	addBlockAt(ImageName::woodPlankMed1, 465,130,85,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodPlankMed1, 537,130,85,12.5,  b2_pi/2, wood);
	addBlockAt(ImageName::woodPlankMed1, 500,180,85,12.5, 0 , wood);
	addBlockAt(ImageName::woodPlankMed1, 480 ,230,85,12.5, b2_pi/2 , wood);
	addBlockAt(ImageName::woodPlankMed1, 520 ,230,85,12.5, b2_pi/2 , wood);
	addBlockAt(ImageName::glassPlankShort1, 485, 130, 42.5, 12.5,  b2_pi/2, glass);
	addBlockAt(ImageName::glassPlankShort1, 515,130, 42.5, 12.5,  b2_pi/2, glass);
	addBlockAt(ImageName::woodPlankMed1, 500,79,200,25, 0, 1000000);

}

void addBlocks9()
{
	float wood = 250.0f;
	float glass = 65.0f;
	float stone = 900.0f;
	addBlockAt(ImageName::stoneBrick1, 480, 132, 50,25, 0, stone);
	addBlockAt(ImageName::stoneBrick1, 562, 132, 50,25, 0, stone);
	addBlockAt(ImageName::stoneBrick1, 295, 132, 50,25, 0, stone);
	addBlockAt(ImageName::stoneBrick1, 210, 132, 50,25, 0, stone);
	addBlockAt(ImageName::woodPlankMed1, 386, 164, 75,12.5, 0, wood);
	//addBlockAt(ImageName::woodMiniPlank1, 480, 132, 25,12.5, 0, wood);pig
	addBlockAt(ImageName::woodBrick1, 511, 171, 50,25, 0, wood);
	addBlockAt(ImageName::woodHalfBrick1, 570, 169, 25,25, 0, wood);
	addBlockAt(ImageName::woodHalfBrick1, 489, 209, 25,25, 0, wood);
	addBlockAt(ImageName::woodBrick1, 553, 211, 50,25, 0, wood);
	addBlockAt(ImageName::woodBrick1, 219, 174, 50,25, 0, wood);
	addBlockAt(ImageName::woodHalfBrick1, 279, 173, 25,25, 0, wood);
	addBlockAt(ImageName::woodBrick1, 259, 216, 50,25, 0, wood);
	addBlockAt(ImageName::woodHalfBrick1, 192, 216, 25,25, 0, wood);
	addBlockAt(ImageName::woodPlankShort1, 180, 283, 42.5,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodPlankShort1, 289, 283, 42.5,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodPlankShort1, 480, 280, 42.5,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodPlankShort1, 580, 281, 42.5,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodPlankMed1, 533, 337, 85,12.5, 0, wood);
	addBlockAt(ImageName::woodPlankMed1, 235, 336, 85,12.5, 0, wood);
	addBlockAt(ImageName::woodBrick1, 172, 390, 50,25, b2_pi/2, wood);
	addBlockAt(ImageName::woodBrick1, 300, 390, 50,25, b2_pi/2, wood);
	addBlockAt(ImageName::woodPlankShort1, 460, 390, 42.5,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodPlankShort1, 482, 391, 42.5,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodPlankShort1, 609, 389, 42.5,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodPlankShort1, 587, 390, 42.5,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodPlankMed1, 535, 445, 85,12.5, 0, wood);
	addBlockAt(ImageName::woodPlankMed1, 238, 445, 85,12.5, 0, wood);
	addBlockAt(ImageName::glassBrick1, 535, 480, 50,25, 0, glass);
	addBlockAt(ImageName::glassBrick1, 234, 477, 50,25, 0, glass);
	addBlockAt(ImageName::woodMiniPlank1, 234, 520, 25,12.5, b2_pi/2, wood);
	addBlockAt(ImageName::woodMiniPlank1, 536, 524, 25,12.5, b2_pi/2, wood);
	


}

void AzulCore::setTargetAndSpeed(float x, float y, float z, float s)
{
	Vect tmp(x,y,z,0);
	cameraTarget = tmp;
	camSpeed = s;
}

void AzulCore::cameraMove()
{
	Camera *pCam = Camera::Instance();
	Vect pos;
	Vect dir;
	Vect lookAt;
	Vect up;
	Vect right;
	Vect newPos;
	pCam->getPos( pos );
	pCam->getDir( dir );
	pCam->getLookAt( lookAt );
	pCam->getUp( up );
	pCam->getRight( right );

	cameraTarget[x]-=400;
	cameraTarget[y]-=300;
	newPos = cameraTarget-pos;
	newPos.norm();
	pos += newPos*camSpeed;
	lookAt[x] = pos[x];
	lookAt[y] = pos[y];
	//printf("%f - %f - %f \n", cameraTarget[x],cameraTarget[y],cameraTarget[z] );

	if( (pos - lookAt).dot( dir ) > 0.02f )
	{
		pCam->setOrientAndPosition( up, lookAt, pos );
	}

	if( pos[z]>0.1f )
	{
		pos[z] = 0.1f;
	}
	if( pos[z]<-2 )
	{
		pos[z] = -2;
	}

	if( pos[y]<36 )
	{
		pos[y] = 36;
		lookAt[y] = 36;
	}
	if( pos[y]>258 )
	{
		pos[y] = 258;
		lookAt[y] = 258;
	}

	if( pos[x]>354 )
	{
		pos[x] = 354;
		lookAt[x] = 354;
	}
	if( pos[x]<-130 )
	{
		pos[x] = -130;
		lookAt[x] = -130;
	}

	pCam->setOrientAndPosition( up, lookAt, pos );

}

void  AzulCore::clearTrails()
{
	while(!smokeTrailLast.empty())
	{
		smokeTrailLast.front()->display = false;
		smokeTrailLast.pop_front();
	}
}

void isBirdDead()
{
	if (!pBird)
		return;
	float angle = pBird->pBody->GetAngularVelocity();
	b2Vec2 vel = pBird->pBody->GetLinearVelocity();
	float delta = 0.04f;

	if( pBird->bState==NORMAL1||pBird->bState==NORMAL2||pBird->bState==NORMAL3 )
	{
		if( angle < delta && fabsf(vel.x) < delta && fabsf(vel.y) < delta ||pBird->flagForDelete )
		{
			statCount++;
			
			if( statCount > 6 ||pBird->flagForDelete)
			{
				deleteBird = Sound::getSoundEngine()->play2D("birdDestroyed.mp3", false, false, true);
				pBird->markForDelete();
				pBird->pGameSprite->display = false;
				pBird->pCircleSprite->display = false;
				pBird->pBody->SetActive(false);
				AzulCore::clearTrails();
				smokeTrailLast = pBird->getTrail();
				delete pBird;
				pBird=0;
				if (birds.empty())
					return;
				statCount = 0;
				pBird=birds.top();
				birds.pop();
				pBird->bState=SLING;
				return;
			}
		}
		else
		{
			statCount = 0;
		}
	}
}

void createBird(float x, float y, float rad)
{
	GameSprite *pBirdSprite = new GameSprite( SpriteBatchName::SpriteBatch_Moving,SpriteName::Sprite_Bird, ImageName::Image_RedBird, Rect(x, y, rad, rad) );
	CircleSprite *pBirdCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Color(Yellow), Rect(x, y+rad*2, rad, rad));
	pBird = new GameObjectBird(GameObjectName::GameObject_Bird, pBirdSprite, pBirdCircle, pWorld, 70.0f  );

	birds.push(pBird);
	//printf("%f\n", pBird->pBody->GetMass());
}

void createYellowBird(float x, float y, float rad)
{
	GameSprite *pBirdSprite = new GameSprite( SpriteBatchName::SpriteBatch_Moving,SpriteName::Sprite_Bird, ImageName::Image_YellowBird, Rect(x, y, rad, rad) );
	CircleSprite *pBirdCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Color(Yellow), Rect(x, y+rad*2, rad, rad));
	pBird = new YellowBird(GameObjectName::GameObject_Bird, pBirdSprite, pBirdCircle, pWorld, 70.0f );
	
	birds.push(pBird);
}

void createGreenBird(float x, float y, float rad)
{
	GameSprite *pBirdSprite = new GameSprite( SpriteBatchName::SpriteBatch_Moving,SpriteName::Sprite_Bird, ImageName::Image_GreenBird, Rect(x+rad, y+rad, rad*1.5f, rad) );
	CircleSprite *pBirdCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Color(Green), Rect(x, y, rad, rad));
	pBird = new GreenBird(GameObjectName::GameObject_Bird, pBirdSprite, pBirdCircle, pWorld, 70.0f );
	GreenBird* b = (GreenBird*) pBird;
	b->first = 1;
	b2Vec2 tmp(0,0);
	b->boom = tmp;
	b->boomtimer = 80;
	
	birds.push(pBird);
}

void createWhiteBird(float x, float y, float rad)
{
	GameSprite *pBirdSprite = new GameSprite( SpriteBatchName::SpriteBatch_Moving,SpriteName::Sprite_Bird, ImageName::Image_WhiteBird, Rect(x, y, rad, rad) );
	CircleSprite *pBirdCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Color(White), Rect(x, y+rad*2, rad, rad));
	pBird = new WhiteBird(GameObjectName::GameObject_Bird, pBirdSprite, pBirdCircle, pWorld, 70.0f  );
	WhiteBird* b = (WhiteBird*) pBird;
	b->setWorld(pWorld);
	
	pBird->bState = GROUND;
	birds.push(pBird);
}

void createBlueBird(float x, float y, float rad)
{
	
	GameSprite *pBirdSprite = new GameSprite( SpriteBatchName::SpriteBatch_Moving,SpriteName::Sprite_Bird, ImageName::Image_BlueBird, Rect(x, y, rad, rad) );
	CircleSprite *pBirdCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Color(Blue), Rect(x, y+rad*2, rad, rad));
	pBird = new BlueBird(GameObjectName::GameObject_Bird, pBirdSprite, pBirdCircle,pWorld, 30.0f  );
	BlueBird* b = (BlueBird*) pBird;
	b->setWorld(pWorld);

	pBird->bState = GROUND;
	birds.push(pBird);
	//printf("%f\n", pBird->pBody->GetMass());
}

void createBlackBird(float x, float y, float rad)
{
	
	GameSprite *pBirdSprite = new GameSprite( SpriteBatchName::SpriteBatch_Moving,SpriteName::Sprite_Bird, ImageName::Image_BlackBird, Rect(x, y, rad, rad+rad*0.3f) );
	CircleSprite *pBirdCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Color(Black), Rect(x, y+rad*2, rad, rad));
	pBird = new BlackBird(GameObjectName::GameObject_Bird, pBirdSprite, pBirdCircle,pWorld, 70.0f  );
	BlackBird* b = (BlackBird*) pBird;
	b->setWorld(pWorld);

	pBird->bState = GROUND;
	birds.push(pBird);
	//printf("%f\n", pBird->pBody->GetMass());
}


void addBirds1()
{
	createYellowBird(140,80,30);
	createWhiteBird(180,80,30);
	createGreenBird(200,80,30);
	createBlueBird(60, 80, 15);
	createBlackBird(20,80,30);
	createBird(100,80,30);
	pBird->bState = SLING;
	birds.pop();
}

void addPigs9()
{

	addPigAt(ImageName::Pig1, 193, 150, 75);
	addPigAt(ImageName::Pig1, 120, 200, 25);
	addPigAt(ImageName::Pig1, 260, 200, 25);


}

void addPigs1()
{

	addHelmetPigAt(ImageName::HelmetPig1, 500, 220, 25);

}


//-----------------------------------------------------------------------------
// AzulCore::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void AzulCore::Initialize()
{
	AZUL_UNUSED( window );

	// Rendering Context
	this->SetupRC();

	// Setup & compile shaders
	shaderManager.InitializeStockShaders();

	// scale
	UnitScale::Create( 50.0f );

	// Setup the managers
    TextMan::Create();
	ImageMan::Create();
	SpriteBatchManager::Create();

    // Initialize timer
	AzulStopWatch::initStopWatch();

	// Start timer
	totalWatch.tic();
	stopWatch.tic();

}



//-----------------------------------------------------------------------------
// AzulCore::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void AzulCore::LoadContent()
{
	
	// Initially setup the camera  (screen size)
	Camera::setViewport( 0, 0, 800, 600);
	Camera::setOrthographic(-400.0f, 400.0f, -300.0f, 300.0f, 1.0f, 1000.0f);
	Camera::setOrientAndPosition( Vect(0.0f,1.0f,0.0f), Vect(0.0f,0.0f, -1.0f), Vect(0.0f,0.0f, 0.00f) );
	 
	// Create and Load textures                   
	loadTextures();
	
	// Create Images
	loadImages();

	// SpriteBatches
	
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Foreground);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Blocks);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Moving);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Background2);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Background);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Debug);

	Vect2D A(110,210);
	Vect2D B(90,210);
	pLine1  = new ScreenLine( SpriteBatchName::SpriteBatch_Background2, SpriteName::Sprite_Poly, 10.0f, Color(Black),  A, B );
	Vect2D C(80,210);
	Vect2D D(90,210);
	pLine2  = new ScreenLine( SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_Poly, 10.0f, Color(Black), C, D );
	
	addBackground();

	// Create Block - object
		GameSprite *pBlockSprite = new GameSprite( SpriteBatchName::SpriteBatch_Blocks,SpriteName::Sprite_Block, ImageName::BLANK, Rect(500, -119.5, 20000, 500) );
		BoxSprite *pBlockBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Block, 2.0f, Vect(0,0,255,255), pBlockSprite);
		GameObjectBlock *pBlock = new GameObjectBlock(GameObjectName::GameObject_Ground, pBlockSprite, pBlockBox, 1000000 );
		
	// Gravity in Y direction
		b2Vec2 gravity(0.0, -10.0f);
		pWorld =  new b2World(gravity);
		AngryContactListener *myContactListener = new AngryContactListener();
		pWorld->SetContactListener( myContactListener );

	// Ground box
		b2BodyDef GroundBoxDef;
		GroundBoxDef.position.Set( PixelToMeter(pBlock->pBoxSprite->posX), PixelToMeter(pBlock->pBoxSprite->posY) );
		b2Body *pGroundBoxBody = pWorld->CreateBody(&GroundBoxDef);
		b2PolygonShape GroundBox;
		GroundBox.SetAsBox( PixelToMeter(pBlock->pBoxSprite->origWidth * 0.5f), PixelToMeter(pBlock->pBoxSprite->origHeight * 0.5f));
		pGroundBoxBody->CreateFixture(&GroundBox, 0.0f);
		pGroundBoxBody->GetFixtureList()->SetUserData(pBlock);
		pGroundBoxBody->SetUserData( pBlock );
		pBlock->pBody = pGroundBoxBody;

		if (level == 1)
		{
			addPigs1();
			addBlocks1();
			addBirds1();
		}

		if (level == 9)
		{
			addPigs9();
			addBlocks9();
			addBirds1();
		}
};


//-----------------------------------------------------------------------------
// AzulCore::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void AzulCore::Update()
{ 
	// Time update.
	//      Get the time that has passed.
	//      Feels backwards, but its not, need to see how much time has passed
		printf("FRAME--------------------------------------------------------------\n" );
		stopWatch.toc();
		stopWatch.tic();
		totalWatch.toc();


	// Add your update below this line: ----------------------------

		// Input tests - quick and dirty
		//               Not complete, but execised enough to prove its works
			MouseTest(window, pBird, pLine1, pLine2, gameObjectList);
			KeyboardTest(window, pBird);
			cameraMove();
			Camera::updateCamera();
			
		// Physics Update - Step world
			int velocityIterations = 6;
			int positionIternations = 3;
			pWorld->Step( 0.0165f, velocityIterations, positionIternations);
		// Update graphics object
			b2Body *pBody = pWorld->GetBodyList();

			while( pBody != 0 )
			{
				GameObject *pGameObj = (GameObject *)pBody->GetUserData();
				if( pGameObj != 0 )
				{
					pGameObj->update( pBody->GetPosition(), pBody->GetAngle());
				}
				else
				{
					assert( pGameObj );
				}

				pBody = pBody->GetNext();
			}
		
			isBirdDead();

			std::list< GameObject *>::iterator it=gameObjectList.begin();
			while( it!=gameObjectList.end() )
			{
					   
				GameObject *pGameObj = *it++;
				if(pGameObj->flagForDelete)
				{
						gameObjectList.remove( pGameObj );
						delete pGameObj;
				}
			}
		
	// Camera System - needs to be updated once per frame
	
   // checking for window quit, leave at bottom of Update()
   if(glfwWindowShouldClose(window))
   {
	   this->Quit();
   }
}

//-----------------------------------------------------------------------------
// AzulCore::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void AzulCore::Draw()
{
   // Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Add Rendering stuff below this line
	SpriteBatchManager::Process();

	// House keeping
	//    Swap buffers
	//    Poll for Events
	glfwSwapBuffers(window);
	glfwPollEvents();
}

//-----------------------------------------------------------------------------
// AzulCore::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void AzulCore::UnLoadContent()
{
	// Todo - fix 
	//	TextureManager::deleteTextures();

	this->ShutdownRC(window);
}


// End of File: AzulCore.cpp