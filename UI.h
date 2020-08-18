#pragma once
#include "gameNode.h"

enum class CURRENT_SCENE
{
	TEMP,						//UI를 띄우지 않는 상태
	INVENTORY_OPEN,				//인벤토리 열었을 때
	SHOP_SALE					//상점에 물건 등록할 때
};

class player;

class UI : public gameNode
{
private:
	CURRENT_SCENE _scene;					//띄어야 할 UI 상태

	Image* _firstWeapon;					//첫 번째 무기 선택시 UI 
	Image* _secondWeapon;					//두 번째 무기 선택시 UI
	Image* _pendant;						//오른쪽 하단 펜던트
	Image* _pendantRing;					//사용 가능 알림

	Image* _currentWeapon;					//현재 들고 있는 웨폰
	Image* _subWeapon;						//두 번째 칸 웨폰
	Image* _playerHpImg;					//플레이어체력바
	Image* _bossHpImg;						//보스체력바

	FloatRect _weapon;						//무기 위치
	FloatRect _portal;						//펜던트 위치
	FloatRect _backBar;						//HP바 고정 렉트
	FloatRect _HpBar;						//HP바 렉트

	int _count;								//펜던트 활성화될 때까지 시간
	int _frameCount;						//맞았을 때 HP바 프레임 돌릴 시간
	int _frameY;							//HP바 프레임Y
	int _bossFrameY;						//보스HP바 프레임Y
	int _moneyFrameY;						//돈주머니 프레임Y

	player* _player;

public:
	UI() {}
	~UI() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void setPlayerHpBar(int playerHp);
	void setBossHpBar(int bossHp);

public:
	CURRENT_SCENE getUIScene() { return _scene; }							//현재 UI 씬 가져가기

public:
	void setUIScene(CURRENT_SCENE scene) { _scene = scene; }				//현재 UI 씬 정해주기

public:
	//플레이어 참조용
	void getPlayerMemoryAddressLink(player* player) { _player = player; }
};

