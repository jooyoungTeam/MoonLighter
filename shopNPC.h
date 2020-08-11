#pragma once
#include "gameNode.h"

enum npcType			// NPC ���� ENUM
{
	NPC_NOMAL,			// �Ϲ� NPC - �ƹ��ų� ����
	NPC_HERO,			// ��� NPC - ������ ����
	NPC_RICH			// ���� NPC - �ʹ� ����� �ʴ� �̻� ����
};

enum npcActionState		// NPC �ൿ ENUM
{
	NPC_IDLE,			// �����ϱ��� ��ȸ?����
	NPC_SHOPPING,		// ������ ���� ����
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
	Image*				_img;				// NPC�� �̹���
	npcType				_npcType;			// NPC�� ����
	npcActionState		_npcActionState;
	npcState			_npcState;			// NPC�� ����
	npcEmotionState     _npcEmotionState;	// NPC�� ��л���

	float				_centerX;			// ���� x
	float				_centerY;			// ���� y
	float				_angle;				// ����

	int					_rndChoiceItem;		// ������ ���� ����
	int					_price;				// �� ������ ����
	bool				_checkItem[4];		// ������ Ȯ�� ����

public:
	shopNPC() {}
	~shopNPC() {}

	HRESULT init();
	void	release();
	void	updadte();
	void	render();
	
	void	comparePrice();					// ���� �� �Լ�

};

