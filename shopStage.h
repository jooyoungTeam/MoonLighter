#pragma once
#include "gameNode.h"
#include "shopNPCManager.h"
#include "tile.h"
#include "itemManager.h"
#include "item.h"

#define SHOPTILEX 32
#define SHOPTILEY 28


class inventory;

enum doorState
{
	DOOR_CLOSE,				// 닫힌 상태
	DOOR_OPEN,				// 열린 상태
	DOOR_OPENING,			// 열리는 상태
	DOOR_CLOSING,			// 닫히는 상태
};

struct tagDisplayStand
{
	Vector2 pos;			// 위치

	item* it;				// 아이템
	int	  settingPrice;		// 플레이어 세팅 가격
	int   rightPrice;		// 알맞은 가격
	int	  count;			// 아이템 개수

	bool  isActive;			// 진열대에 아이템이 있냐?

	void init(Vector2 mPos, item* mIt, int mPrice, int mCount, bool mIsActive)
	{
		pos = mPos;
		it = mIt;
		settingPrice = mPrice;
		count = mCount;
		isActive = mIsActive;
	}
};

class shopStage : public gameNode
{
private:
	// =============== 기본 ===============f
	Image* _backGround;				// 배경 이미지
	Image* _celler;					// 판매원 이미지
	class player* _player;				// 플레이어
	float _cellerFrameTimer;
	int	  _cellerIndex;

	// =========== 아이템 & 인벤 ===========
	inventory* _inventory;				// 아이템 매니저
	tagDisplayStand _display[4];	// 진열대

	// =============== 문 =================
	doorState _doorState;			// 문 상태
	FloatRect  _doorRC;					// 문 렉트
	int	  _doorFrameTimer;			// 문 프레임 타이머
	int   _doorIndex;				// 문 인덱스

	// ============== NPC =================
	shopNPCManager* _npcM;			// NPC 매니저
	bool  _enterNPC;				// NPC 들어오는지 확인



	DWORD             _attribute[SHOPTILEX * SHOPTILEY];
	tagTile			  _tile[SHOPTILEX * SHOPTILEY];


public:
	shopStage() {}
	~shopStage() {}

public:
	HRESULT init();
	void render();
	void update();
	void release();
	void loadMap();
	void renderMap();
	void disPlaySet();				// 진열대 세팅
	void disPlayUpdate();			// 진열대 업데이트
	void doorUpdate();				// 문 업데이트

	void buyItem();					// 아이템 구매
	
public:
	//============================ Get ===========================

	
	void setPlayerLink(player* player) { _player = player; };
public:
	//============================ Set ===========================

};

