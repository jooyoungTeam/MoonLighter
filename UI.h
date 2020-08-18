#pragma once
#include "gameNode.h"

enum class CURRENT_SCENE
{
	TEMP,						//UI를 띄우지 않는 상태
	INVENTORY_OPEN,				//인벤토리 열었을 때
	SHOP_SALE					//상점에 물건 등록할 때
};

enum class BOSS_STAGE
{
	NOT_BOSS,
	PLAYER_ENTER,				//플레이어 보스 스테이지 입장
	BOSS_APEEAR,
	STAGE_START					//보스 스테이지 시작 (인벤토리 사용 가능?)
};

class player;
class boss;

class UI : public gameNode
{
private:
	CURRENT_SCENE _scene;					//띄어야 할 UI 상태
	BOSS_STAGE _bossStage;					//보스 UI 상태

	Image* _pendant;						//오른쪽 하단 펜던트
	Image* _pendantRing;					//사용 가능 알림

	Image* _playerHpImg;					//플레이어체력바
	Image* _bossHpImg;						//보스체력바

	FloatRect _weapon;						//무기 위치
	FloatRect _portal;						//펜던트 위치
	FloatRect _backBar;						//HP바 고정 렉트
	FloatRect _HpBar;						//HP바 렉트
	FloatRect _bossBackBar;					//보스 HP바 고정 렉트
	FloatRect _bossHpBar;					//보스 HP바 렉트

	int _count;								//펜던트 활성화될 때까지 시간
	int _bossCount;							//보스 방 입장 한 후 시간
	int _alphaCount;						//플레이어 hit 일 때 화면 깜박이는 제한카운트
	int _frameCount;						//맞았을 때 HP바 프레임 돌릴 시간
	int _frameY;							//HP바 프레임Y
	int _bossFrameY;						//보스HP바 프레임Y
	int _moneyFrameY;						//돈주머니 프레임Y

	float _hpWidth;							//플레이어 체력바 너비
	float _bossHpWidth;						//보스 체력바 너비
	float _alpha;

	bool _isHit;							//플레이어 맞을 때
	bool _bossHit;							//보스 맞을 때

	player* _player;
	boss* _boss;

public:
	UI() {}
	~UI() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void setPlayerHpBar();
	void setBossHpBar();
	void draw();
	void setMoneyBag();

public:
	CURRENT_SCENE getUIScene() { return _scene; }							//현재 UI 씬 가져가기
	BOSS_STAGE getBossScene() { return _bossStage; }						//현재 보스 씬 가져가기

public:
	void setUIScene(CURRENT_SCENE scene) { _scene = scene; }				//현재 UI 씬 정해주기
	void setBossScene(BOSS_STAGE stage) { _bossStage = stage; }				//현재 보스 씬 정해주기
	void setBossY(int y) { _bossFrameY = y; }								//임시
	void setAlpha(float a) { _alpha = a; }

public:
	//플레이어 참조용
	void getPlayerMemoryAddressLink(player* player) { _player = player; }
	//보스 참조용
	void getBossMemoryAddressLink(boss* boss) { _boss = boss; }
};

