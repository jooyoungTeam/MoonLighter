#pragma once

#define TILESIZE 50

#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002


enum TERRAIN
{
	TR_WALL, TR_FLOOR, TR_CEMENT, TR_GRASS, TR_WATER, TR_NONE, TR_END
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
	bool    isColTile;
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