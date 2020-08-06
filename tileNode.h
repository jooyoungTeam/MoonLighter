#pragma once

#define TILESIZE 32

#define TILEX 20
#define TILEY 20


#define TILESIZEX (TILESIZE * TILEX)
#define TILESIZEY (TILESIZE * TILEY)

#define SAMPLETILEX 9
#define SAMPLETILEY 1

enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
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
	POS_FLAG1,POS_FLAG2,
	POS_TANK1,POS_TANK2,
};

struct tagTile
{
	TERRAIN terrain;
	OBJECT  object;
	RECT    rc;
	int     terrainFrameX;
	int     terrainFrameY;
	int     objFrameX;
	int     objFrameY;
	bool    isDrag;
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