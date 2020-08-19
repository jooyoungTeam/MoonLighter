#pragma once

#define TILESIZE 50

#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002
#define TP_TOWN         10000
#define TP_SHOP         10001
#define TP_ENTERENCE    10002
#define TP_DUN1         10003
#define TP_DUN2         10004
#define TP_DUN3         10005
#define TP_SPA          10006
#define TP_BOSS         10007

enum TERRAIN
{
	TR_WALL, TR_FLOOR, TR_CEMENT, TR_GRASS, TR_WATER, TR_POS,TR_NONE, TR_END
};

enum ACTIVEPOS
{
	POS_TOWN, POS_SHOP, POS_ENTERENCE,   POS_DUN1, POS_DUN2, POS_DUN3, POS_SPA, POS_BOSS, POS_NONE,   // æ¿ ¿¸»Ø ≈∏¿œ
};

struct tagTile
{
	ACTIVEPOS pos;
	TERRAIN   terrain;
	RECT      rc;
	int       terrainFrameX;
	int       terrainFrameY;
	bool      isDrag;
	int       idX;
	int       idY;
	bool      isColTile;
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
