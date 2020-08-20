#pragma once
#include "gameNode.h"

enum potionMakeState
{
	POTION_INIT,
	POTION_SIZE,
	POTION_CHECK
};

enum potionEffectState
{
	POTION_E_NULL,
	POTION_E_INIT,
	POTION_E_START,
	POTION_E_MID,
	POTION_E_END
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
	potionEffectState _effectState;
	Image* _select;
	Image* _makeMaterial;
	Image* _makeItem;
	Image* _effectImg;

	Vector2 _selectPt;
	Vector2 _pt[4];

	tagPotionInfo _selectPotion;
	tagPotionInfo _potion[4];

	int _makeItemY;
	int _makeMaterialY;

	int _selectIndex;

	int _makeCount;

	int _effectIndex;
	float _effectTimer;

	bool _isSizeLeft;		// 개수 줄이기
	bool _isSizeRight;		// 개수 늘리기
	bool _isPotionCheck;	// 
	bool _isActive;			// 상점 활성화
	bool _isBuy;			// 살 수 있는지?
	bool _isEnd;			// 끝났는지?

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


