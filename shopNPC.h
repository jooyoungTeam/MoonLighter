#pragma once
#include "gameNode.h"
#include "aStar.h"
#include "item.h"

enum npcType			// NPC ���� ENUM
{
	NPC_NOMAL,			// �Ϲ� NPC - �ƹ��ų� ����
	NPC_HERO,			// ��� NPC - ������ ����
	NPC_RICH			// ���� NPC - �ʹ� ����� �ʴ� �̻� ����
};

enum npcActionState		// NPC �ൿ ENUM
{
	NPC_ENTER,			// NPC ����
	NPC_IDLE,			// NPC �������ִ� ����
	NPC_WALK,			// �����ϱ��� ��ȸ?����
	NPC_SHOPPING,		// ������ ���� ����
	NPC_CHECKITEM,		// ������ Ȯ�� ����
	NPC_BUY,			// ������ ���� ����
	NPC_AWAY			// ������ ����
};

enum npcState			// NPC ���� ENUM
{
	NPC_LEFT,			// ���� ���� ����
	NPC_UP,				// ���� ���� ����
	NPC_RIGHT,			// ������ ���� ����
	NPC_DOWN			// �Ʒ� ���� ����
};

enum npcEmotionState	// NPC ��� NUM
{
	NPC_CHOOSE,			// ���� ����
	NPC_TOO_EXPENSIVE,	// �ʹ� ���
	NPC_EXPENSIVE,		// ���
	NPC_CHEAP,			// ������
	NPC_TOO_CHEAP		// �ʹ� ������
};


class shopNPC : public gameNode
{
private:
	aStar*				_aStar;				// A*
	item*				_item;				// ����ִ� ������
	Image*				_img;				// NPC�� �̹���
	Image*				_emotionImg;		// ��� �̹���
	npcType				_npcType;			// NPC�� ����
	npcActionState		_npcActionState;	// NPC �ൿ ����
	npcState			_npcState;			// NPC�� ����
	npcEmotionState     _npcEmotionState;	// NPC�� ��л���
	vector<POINT>		_vUnMove;			// ������ ��
	RECT				_rc;				// NPC ��Ʈ

	POINT				_goToPoint;			// ���� �Ұ�
	POINT				_itemWayPoint[4];	// ������ ���� ��ǥ
	POINT				_counterPoint;		// ī���� ��ǥ
	POINT				_aroundPoint[4];	// ��ȸ ��ǥ

	float				_centerX;			// ���� x
	float				_centerY;			// ���� y
	float				_thinkBoxX;			// ��ǳ�� x
	float				_thinkBoxY;			// ��ǳ�� y
	float				_angle;				// ����
	float				_frameTimer;		// ������Ÿ�̸�
	float				_delayTimer;		// ������Ÿ�̸�
	float				_emotionFrameTimer;	// �̸�� ������Ÿ�̸�

	int					_indexX;			// �������ε���X
	int					_indexY;			// �������ε���Y
	int					_emotionIndexX;		// �̸�� �������ε��� X
	int					_rndChoiceItem;		// ������ ���� ����
	int					_rightPrice;		// ������ ������
	int					_settingPrice;		// �÷��̾ ���� ����
	int					_selectPrice;		// �� ������ ����
	int					_checkItemCount;	// ������ Ȯ���� ��

	bool				_checkItem[4];		// ������ Ȯ�� ����(�Ȱ��� ������ �Ⱥ���)
	bool				_isBuy;				// �����ߴ��� Ȯ��
public:
	shopNPC() {}
	~shopNPC() {}

public:
	HRESULT init();
	void	release();
	void	updadte();
	void	render();
	
	void	frameUpdate();					// ������ ������Ʈ
	void	emotionFrameUpdate();			// �̸�� ������ ������Ʈ
	void	move();							// npc �̵�
	void	comparePrice();					// ���� ��
	void	unMoveSet();					// �� �����̴°� ����
	void    wayPointSet();					// ���ߵǴ°� ����
	void	directionCheck();				// ���� �˻�
	void	chooseItem();					// ������ �̱�.

public:
	//============================ Get ===========================
	npcActionState getNPCActionState() { return _npcActionState; }
	npcEmotionState getNPCEmotionState() { return _npcEmotionState; }
	RECT getNPCRect() { return _rc; }
	int  getSelectPrice() { return _selectPrice; }
	int  getRndItem() { return _rndChoiceItem; }

public:
	//============================ Set ===========================
	void setSettingPrice(int price) { _settingPrice = price; }
	void setRightPrice(int price) { _rightPrice = price; }
	void setItem(item* item) { _item = item; }
};

