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
};

class potionCreate : public gameNode
{
private:
	potionMakeState _state;
	Image* _selectPotion;

	Vector2 _selectPt;
	Vector2 _pt[4];

	tagPotionInfo _potion[4];

	int _selectIndex;

	bool _isSizeLeft;
	bool _isSizeRight;
	bool _isPotionCheck;
	bool _isActive;

public:
	potionCreate() {}
	~potionCreate() {}


public:
	HRESULT init();
	void update();
	void render();
	void release();
	void potionSet();


};


