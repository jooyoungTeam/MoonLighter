#pragma once
#include "gameNode.h"

struct tagMiniMap
{
	FloatRect     rc;
	bool          isDraw;
};

class miniMap : public gameNode
{
private:
	vector<tagMiniMap*> _vMiniMap;
	Image*              _miniMapImg;
	FloatRect           _miniMapMove;
	FloatRect           _miniMap;
	int                 _tileX, _tileY;
	int                 _mapY;
	float               _tileSize;
	float               _scale;
	POINT				_playerPos;
public:
	miniMap() {}
	~miniMap() {}
public:
	HRESULT init(int x, int y);
	void    render(objectManager* obj,POINT playerPos);
	void    update();
	void    release();
	void    setImage(Image* img) { _miniMapImg = img; }
	void    setIsDraw(int arrNum, bool isDraw) { _vMiniMap[arrNum]->isDraw = isDraw; }
	
};

