#pragma once
#include "gameNode.h"

enum potionMakeState
{
	POTION_INIT,
	POTION_SIZE,
	POTION_CHECK
};

struct tagPotionInfo
{
	int index;
	int price;
	Image* img;
	wstring name;
	wstring discription;

	Image* needItem;
	int needIndex;
	int needCount;
};

class potionCreate : public gameNode
{
private:
	potionMakeState _state;
	Image* _select;

	Vector2 _selectPt;
	Vector2 _pt[4];

	tagPotionInfo _selectPotion;
	tagPotionInfo _potion[4];

	int _selectIndex;

	int _makeCount;

	int _effectIndex;
	float _effectTimer;

	bool _isSizeLeft;
	bool _isSizeRight;
	bool _isPotionCheck;
	bool _isActive;
	bool _isBuy;

public:
	potionCreate() {}
	~potionCreate() {}


public:
	HRESULT init();
	void update();
	void render();
	void release();
	void indexSet();
	void potionSet();
	void reset();
	void isSizeUpdate();
	void isBuyUpdate();

public:
	void setIsActive(bool active) { _isActive = active; }
	

public:
	bool getIsActive() { return _isActive; }


};


