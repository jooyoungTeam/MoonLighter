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
	DOOR_CLOSE,				// ���� ����
	DOOR_OPEN,				// ���� ����
	DOOR_OPENING,			// ������ ����
	DOOR_CLOSING,			// ������ ����
};

class shopStage : public gameNode
{
private:
	// =============== �⺻ ===============f
	Image* _backGround;				// ��� �̹���
	Image* _celler;					// �Ǹſ� �̹���
	class player* _player;			// �÷��̾�
	float _cellerFrameTimer;
	int	  _cellerIndex;

	bool  _isCeller;
	FloatRect _interactionRC;		// ��ȣ�ۿ� ��Ʈ

	// =========== ������ & �κ� ===========
	inventory* _inventory;			// ������ �Ŵ���
	display* _display1;	// ������
	display* _display2;	// ������
	display* _display3;	// ������
	display* _display4;	// ������

	int _activeDisplayCount;		// ��밡���� ������ ī��Ʈ

	// =============== �� =================
	doorState _doorState;			// �� ����
	FloatRect  _doorRC;					// �� ��Ʈ
	int	  _doorFrameTimer;			// �� ������ Ÿ�̸�
	int   _doorIndex;				// �� �ε���

	// ============== NPC =================
	shopNPCManager* _npcM;			// NPC �Ŵ���
	bool  _enterNPC;				// NPC �������� Ȯ��

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
	void disPlaySet();				// ������ ����
	void disPlayUpdate();			// ������ ������Ʈ
	void doorUpdate();				// �� ������Ʈ
	void npcProcess();				// NPC ������Ʈ
	void npcSet();					// NPC �ൿ ����

public:
	//============================ Get ===========================
	FloatRect getInteractionRC() { return _interactionRC; }
public:
	//============================ Set ===========================
	void setPlayerLink(player* player) { _player = player; };

};

