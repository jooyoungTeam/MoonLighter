#pragma once
#include "gameNode.h"

enum class ITEMTYPE
{
	SLIME_RED, SLIME_BLUE, SLIME_YELLOW,
	VINE, WOOD, FABRIC, GOLEM_PIECES,
	BROKEN_SWORD, CRYSTAL_ENERGY, REINFORCED_STEEL, GOLEM_CORE,
	GOLEMKING_CRYSTAL, GOLEMKING_RECORD,
	POTION_S
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
	int getIndex() { return _itemIndex; }					//������ �ε��� ��ȣ ��������
	FloatRect getRc() { return _rc; }						//������ ��Ʈ ��������
	Image* getImg() { return _img; }						//������ �̹��� ��������
};

