#pragma once
#include "gameNode.h"

class player;

class UI : public gameNode
{
private:
	Image* _firstWeapon;					//첫 번째 무기 선택시 UI 
	Image* _secondWeapon;					//두 번째 무기 선택시 UI
	Image* _pendant;						//오른쪽 하단 펜던트
	Image* _pendantRing;					//사용 가능 알림

	Image* _currentWeapon;
	Image* _subWeapon;
	Image* _HPbar;

	FloatRect _weapon;						//무기 위치
	FloatRect _portal;						//펜던트 위치

	int _count;								//펜던트 활성화될 때까지 시간
	bool _weaponChange;						//무기 UI 바꿀 용도

	player* _player;

public:
	UI() {}
	~UI() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void setUIHp();

public:
	bool getWeaponChange() { return _weaponChange; }

public:
	void setWeaponChagne(BOOL change = FALSE) { _weaponChange = change; }

public:
	//플레이어 참조용
	void getPlayerMemoryAddressLink(player* inven) { _player = inven; }
};

