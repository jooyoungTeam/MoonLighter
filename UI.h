#pragma once
#include "gameNode.h"

enum class CURRENT_SCENE
{
	TEMP,						//UI를 띄우지 않는 상태
	INVENTORY,					//인벤토리 열었을 때
	SHOP_SALE					//상점에 물건 등록할 때
};

class player;
class inventory;

class UI : public gameNode
{
private:
	CURRENT_SCENE _scene;

	Image* _firstWeapon;					//첫 번째 무기 선택시 UI 
	Image* _secondWeapon;					//두 번째 무기 선택시 UI
	Image* _pendant;						//오른쪽 하단 펜던트
	Image* _pendantRing;					//사용 가능 알림

	Image* _currentWeapon;					//현재 들고 있는 웨폰
	Image* _subWeapon;						//두 번째 칸 웨폰
	Image* _HPbar;							//체력바

	FloatRect _weapon;						//무기 위치
	FloatRect _portal;						//펜던트 위치

	int _count;								//펜던트 활성화될 때까지 시간
	bool _weaponChange;						//무기 UI 바꿀 용도

	player* _player;
	inventory* _inven;

public:
	UI() {}
	~UI() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void setUIHp(int playerHp);

public:
	CURRENT_SCENE getUIScene() { return _scene; }							//현재 UI 씬 가져가기
	bool getWeaponChange() { return _weaponChange; }						//현재 웨폰 어떤 상태인지 가져가기

public:
	void setUIScene(CURRENT_SCENE scene) { _scene = scene; }				//현재 UI 씬 정해주기
	void setWeaponChagne(BOOL change = FALSE) { _weaponChange = change; }	//플레이어 웨폰과 연동해서 설정해주기

public:
	//플레이어 참조용
	void getPlayerMemoryAddressLink(player* player) { _player = player; }
	//인벤토리 참조용
	void getInvenMemoryAddressLink(inventory* inven) { _inven = inven; }
};

