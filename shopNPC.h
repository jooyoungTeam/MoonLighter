#pragma once
#include "gameNode.h"
#include "aStar.h"

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
	aStar*				_aStar;
	Image*				_img;				// NPC�� �̹���
	npcType				_npcType;			// NPC�� ����
	npcActionState		_npcActionState;
	npcState			_npcState;			// NPC�� ����
	npcEmotionState     _npcEmotionState;	// NPC�� ��л���
	vector<POINT>		_vUnMove;

	POINT				_goToPoint;			// ���� �Ұ�
	POINT				_itemWayPoint[4];	// ������ ���� ��ǥ
	POINT				_counterPoint;		// ī���� ��ǥ
	POINT				_aroundPoint[4];	// ��ȸ ��ǥ

	float				_centerX;			// ���� x
	float				_centerY;			// ���� y
	float				_angle;				// ����
	float				_frameTimer;		// ������Ÿ�̸�
	float				_delayTimer;

	int					_indexX;			// �������ε���X
	int					_indexY;			// �������ε���Y
	int					_aStarIndex;		// ���̽�Ÿ �ε���
	int					_rndChoiceItem;		// ������ ���� ����
	int					_price;				// �� ������ ����
	int					_checkItemCount;

	bool				_checkItem[4];		// ������ Ȯ�� ����(�Ȱ��� ������ �Ⱥ���)

public:
	shopNPC() {}
	~shopNPC() {}

	HRESULT init();
	void	release();
	void	updadte();
	void	render();
	
	void	comparePrice();					// ���� �� �Լ�

	void	unMoveSet();					// �� �����̴°� ����
	void    wayPointSet();					// ���ߵǴ°� ����

	void	directionCheck();				// ���� �˻�
	void	chooseItem();					// ������ �̱�
};

