#pragma once

#define TILESIZE 50

#define TILEX 40
#define TILEY 30

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
	OBJ_HOUSE, OBJ_ARCHITECTURE, OBJ_DOOR,
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
	int     idX;
	int     idY;
	string  str;
};


struct tagSampleObject
{
	RECT    rc;
	int     objFrameX;
	int     objFrameY;
};

struct tagObject
{
	RECT     rc;
	Image*   img;
	bool     isFrameRender;
	int      frameX;
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