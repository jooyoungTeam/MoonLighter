#pragma once
#include "gameNode.h"
#include "player.h"
#include "shopNPC.h"
#include "tile.h"
#include "itemManager.h"
#include "item.h"

enum doorState
{
	DOOR_CLOSE,				// ���� ����
	DOOR_OPENING,			// ������ ����
	DOOR_CLOSING,			// ������ ����
	DOOR_DELAY				// ������ ����
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
	player* _player;				// �÷��̾�

	// =========== ������ & �κ� ===========
	itemManager* _im;				// ������ �Ŵ���
	tagDisplayStand _display[4];	// ������

	// =============== �� =================
	doorState _doorState;			// �� ����
	RECT  _doorRC;					// �� ��Ʈ
	int	  _doorFrameTimer;			// �� ������ Ÿ�̸�
	int   _doorIndex;				// �� �ε���

	// ============== NPC =================
	shopNPC* _shopNPC;				// NPC
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

public:
	//============================ Get ===========================


public:
	//============================ Set ===========================

};

