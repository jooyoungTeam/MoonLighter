#pragma once
#include "gameNode.h"

#define SAMPLETILEX 9
#define SAMPLETILEY 7

class palette : public gameNode
{
private:
	RECT                _sampleTileUI; // 팔레트 그림 있는곳
	tagSampleTile       _sampleTile[SAMPLETILEX * SAMPLETILEY];
	RECT                _sampleTileOnOff;
	bool                _isActive;

public:
	palette() {}
	~palette() {}
public:
	HRESULT init();
	void    update();
	void    render();
	void    release();
public:
	void    sampleTileRender();
	void    selectTile(POINT& currentPos, RECT& currentRect);
	void    sampleOnOff();
public:
	bool    getIsActive() { return _isActive; }
	RECT    getSampleUIRect() { return _sampleTileUI; }
	RECT    getSampleOnOffRect() { return _sampleTileOnOff; }
};

