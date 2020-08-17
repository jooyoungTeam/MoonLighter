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
	DOOR_CLOSE,				// ���� ����
	DOOR_OPEN,				// ���� ����
	DOOR_OPENING,			// ������ ����
	DOOR_CLOSING,			// ������ ����
};

struct tagDisplayStand
{
	Vector2 pos;			// ��ġ

	item* it;				// ������
	int	  settingPrice;		// �÷��̾� ���� ����
	int   rightPrice;		// �˸��� ����
	int	  count;			// ������ ����

	bool  isActive;			// �����뿡 �������� �ֳ�?

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
	// =============== �⺻ ===============f
	Image* _backGround;				// ��� �̹���
	Image* _celler;					// �Ǹſ� �̹���
	class player* _player;				// �÷��̾�
	float _cellerFrameTimer;
	int	  _cellerIndex;

	// =========== ������ & �κ� ===========
	inventory* _inventory;				// ������ �Ŵ���
	tagDisplayStand _display[4];	// ������

	// =============== �� =================
	doorState _doorState;			// �� ����
	FloatRect  _doorRC;					// �� ��Ʈ
	int	  _doorFrameTimer;			// �� ������ Ÿ�̸�
	int   _doorIndex;				// �� �ε���

	// ============== NPC =================
	shopNPCManager* _npcM;			// NPC �Ŵ���
	bool  _enterNPC;				// NPC �������� Ȯ��



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
	void disPlaySet();				// ������ ����
	void disPlayUpdate();			// ������ ������Ʈ
	void doorUpdate();				// �� ������Ʈ

	void buyItem();					// ������ ����
	
public:
	//============================ Get ===========================

	
	void setPlayerLink(player* player) { _player = player; };
public:
	//============================ Set ===========================

};

