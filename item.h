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
	int _limitCount;
	int _price;

public:
	item() {}
	~item() {}

	HRESULT init(ITEMTYPE type, float x, float y);
	void render();
	void update();
	void release();
	
	void sort();

public:
	FloatRect getRc() { return _rc; }						//아이템 렉트 가져가기
	Image* getImg() { return _img; }						//아이템 이미지 가져가기
	int getIndex() { return _itemIndex; }					//아이템 인덱스 번호 가져가기
	int getLimit() { return _limitCount; }					//아이템 개수 한계치 가져가기
	int getPrice() { return _price; }						//아이템 가격 가져가기
};

