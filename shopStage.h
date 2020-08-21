#pragma once
#include "gameNode.h"
#include "shopNPCManager.h"
#include "display.h"
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

class shopStage : public gameNode
{
private:
	// =============== 기본 ===============f
	Image* _backGround;				// 배경 이미지
	Image* _celler;					// 판매원 이미지
	class player* _player;			// 플레이어
	float _cellerFrameTimer;
	int	  _cellerIndex;

	bool  _isCeller;
	FloatRect _interactionRC;		// 상호작용 렉트

	// =========== 아이템 & 인벤 ===========
	inventory* _inventory;			// 아이템 매니저
	display* _display1;	// 진열대
	display* _display2;	// 진열대
	display* _display3;	// 진열대
	display* _display4;	// 진열대

	int _activeDisplayCount;		// 사용가능한 진열대 카운트

	// =============== 문 =================
	doorState _doorState;			// 문 상태
	FloatRect  _doorRC;					// 문 렉트
	int	  _doorFrameTimer;			// 문 프레임 타이머
	int   _doorIndex;				// 문 인덱스

	// ============== NPC =================
	shopNPCManager* _npcM;			// NPC 매니저
	bool  _enterNPC;				// NPC 들어오는지 확인

	float _npcAddCount;
	bool  _isMaxNpc;

	vector<POINT> _unMoveTile;
	


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
	void npcProcess();				// NPC 업데이트
	void npcSet();					// NPC 행동 셋팅

public:
	//============================ Get ===========================
	FloatRect getInteractionRC() { return _interactionRC; }
public:
	//============================ Set ===========================
	void setPlayerLink(player* player) { _player = player; };

};

