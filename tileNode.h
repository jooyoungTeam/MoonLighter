#pragma once

#define TILESIZE 50

#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002
#define TP_TOWN         0x00000004
#define TP_SHOP         0x00000008
#define TP_ENTERENCE    0x00000016
#define TP_DUN1         0x00000032
#define TP_DUN2         0x00000064
#define TP_DUN3         0x00000128
#define TP_SPA          0x00000256
#define TP_BOSS         0x00000512

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

struct tagMiniMap
{
	FloatRect     rc;
	bool          isDraw;
};