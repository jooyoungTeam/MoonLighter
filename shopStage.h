#pragma once
#include "gameNode.h"
#include "player.h"
#include "shopNPC.h"
#include "tile.h"
#include "itemManager.h"
#include "item.h"

class inventory;

enum doorState
{
	DOOR_CLOSE,				// 닫힌 상태
	DOOR_OPENING,			// 열리는 상태
	DOOR_CLOSING,			// 닫히는 상태
	DOOR_DELAY				// 딜레이 상태
};

struct tagDisplayStand
{
	Vector2 pos;			// 위치

	item* it;				// 아이템
	int	  settingPrice;		// 플레이어 세팅 가격
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
	// =============== 기본 ===============
	Image* _backGround;				// 배경 이미지
	player* _player;				// 플레이어

	// =========== 아이템 & 인벤 ===========
	inventory* _inventory;				// 아이템 매니저
	tagDisplayStand _display[4];	// 진열대

	// =============== 문 =================
	doorState _doorState;			// 문 상태
	RECT  _doorRC;					// 문 렉트
	int	  _doorFrameTimer;			// 문 프레임 타이머
	int   _doorIndex;				// 문 인덱스

	// ============== NPC =================
	shopNPC* _shopNPC;				// NPC
	bool  _enterNPC;				// NPC 들어오는지 확인

public:
	shopStage() {}
	~shopStage() {}

public:
	HRESULT init();
	void render();
	void update();
	void release();


	void disPlaySet();				// 진열대 세팅
	void disPlayUpdate();			// 진열대 업데이트
	void doorUpdate();				// 문 업데이트

	void buyItem();					// 아이템 구매

public:
	//============================ Get ===========================


public:
	//============================ Set ===========================

};

