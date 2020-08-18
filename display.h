#pragma once
#include "gameNode.h"

class shopNPCManager;

class display : public gameNode
{
private:
	shopNPCManager* _npcM;
	int	_index;				// 디스플레이 번호
	Vector2 _pos;			// 위치
	FloatRect _rc;			// 렉트

	item* _it;				// 아이템
	int	  _settingPrice;		// 플레이어 세팅 가격
	int   _rightPrice;		// 알맞은 가격
	int	  _count;			// 아이템 개수

	float _maxY;
	float _minY;
		  
	bool  _isActive;			// 진열대에 아이템이 있냐?
	bool  _isPeople;			// 진열대에 사람이 있냐?

	bool  _direction;

public:
	HRESULT init(int index, Vector2 mPos, item* mIt, int mPrice, int mCount, bool mIsActive);
	void update();
	void render();
	void release();

	void itemMove();

public:
	void setMemoryAdressLinkNpcManager(shopNPCManager* npcM) { _npcM = npcM; }
};

