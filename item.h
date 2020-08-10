#pragma once
#include "gameNode.h"

enum class ITEMTYPE
{
	SLIME_RED, SLIME_BLUE, SLIME_YELLOW
};

class item : public gameNode
{
private:
	ITEMTYPE _type;
	FloatRect _rc;
	Image* _img;
	float _x, _y;
	int _itemIndex;

public:
	HRESULT init(ITEMTYPE type, float x, float y);
	void release();
	void update();
	void render();
	
	void sort();

public:
	int getIndex() { return _itemIndex; }					//아이템 인덱스 번호 가져가기
};

