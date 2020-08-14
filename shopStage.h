#pragma once
#include "gameNode.h"
#include "player.h"
#include "shopNPCManager.h"
#include "tile.h"
#include "itemManager.h"
#include "item.h"

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
	// =============== �⺻ ===============
	Image* _backGround;				// ��� �̹���
	Image* _celler;					// �Ǹſ� �̹���
	player* _player;				// �÷��̾�
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


public:
	shopStage() {}
	~shopStage() {}

public:
	HRESULT init();
	void render();
	void update();
	void release();


	void disPlaySet();				// ������ ����
	void disPlayUpdate();			// ������ ������Ʈ
	void doorUpdate();				// �� ������Ʈ

	void buyItem();					// ������ ����

public:
	//============================ Get ===========================


public:
	//============================ Set ===========================

};

