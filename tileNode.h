#pragma once

#define TILESIZE 50

#define TILEX 100
#define TILEY 100

#define TILESIZEX (TILESIZE * TILEX)
#define TILESIZEY (TILESIZE * TILEY)

#define SAMPLETILEX 9
#define SAMPLETILEY 3

#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002


enum TERRAIN
{
	TR_WALL, TR_FLOOR, TR_GRASS, TR_WATER, TR_NONE, TR_END
};

enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2,
	OBJ_NONE,
};

enum POS
{
	POS_FLAG1, POS_FLAG2,
	POS_TANK1, POS_TANK2,
};

struct tagTile
{
	TERRAIN terrain;
	RECT    rc;
	int     terrainFrameX;
	int     terrainFrameY;
	bool    isDrag;
	string  str;
};

enum MAPMOVE
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_NULL
};

struct tagObject
{
	OBJECT  object;
	Image*  img;
	RECT    rc;
	int     objFrameX;
	int     objFrameY;
};


struct tagMapMove
{
	int x, y;
	RECT rc;
};


struct tagSampleTile
{
	RECT rc;
	int  terrainFrameX;
	int  terrainFrameY;
};

struct tagDragRect
{
	RECT  rc;
	bool  isDraw;
	POINT startPos;
	POINT endPos;
};