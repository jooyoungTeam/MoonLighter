#pragma once
#include "gameNode.h"
#include "aStar.h"
#include "item.h"

enum npcType			// NPC ���� ENUM
{
	NPC_NOMAL,			// �Ϲ� NPC
	NPC_HERO,			// ��� NPC 
	NPC_RICH			// ���� NPC 
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
	NPC_EMOTION_NULL,	// ���»���
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
	Image*				_itemImg;			// ����ִ� ������
	Image*				_img;				// NPC�� �̹���
	Image*				_emotionImg;		// ��� �̹���
	npcType				_npcType;			// NPC�� ����
	npcActionState		_npcActionState;	// NPC �ൿ ����
	npcState			_npcState;			// NPC�� ����
	npcEmotionState     _npcEmotionState;	// NPC�� ��л���
	vector<POINT>		_vUnMove;			// ������ ��
	FloatRect			_rc;				// NPC ��Ʈ

	POINT				_goToPoint;			// ���� �Ұ�
	POINT				_itemWayPoint[4];	// ������ ���� ��ǥ
	POINT				_counterPoint;		// ī���� ��ǥ
	POINT				_aroundPoint[3];	// ��ȸ ��ǥ
	POINT				_eixtPoint;			// ���Թ� ��ǥ

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
	int					_oldRndChoiceItem;  // �ߺ� ���� ���� ��
	int					_rndChoicePt;		// ��ȸ ����
	int					_rightPrice;		// ������ ������
	int					_settingPrice;		// �÷��̾ ���� ����
	int					_selectPrice;		// �� ������ ����
	int					_checkItemCount;	// ������ Ȯ���� ��
	int					_idleCount;			// ��ȸ ī��Ʈ

	bool				_checkItem[4];		// ������ Ȯ�� ����(�Ȱ��� ������ �Ⱥ���)
	bool				_isAnotherPerson[4];// �ٸ������ �ڱⰡ �� �������� �����ִ���'
	bool				_isBuy;				// �����ߴ��� Ȯ��
	bool				_isAway;			// �������� Ȯ��
	bool				_isCount;			// ��������� Ȯ��	
	bool				_isExist;			// ������ �ֳ�?
public:
	shopNPC() {}
	~shopNPC() {}

public:
	HRESULT init(npcType type, vector<POINT> vUnMove);
	void	release();
	void	updadte();
	void	render();
	
	void	frameUpdate();					// ������ ������Ʈ
	void	emotionFrameUpdate();			// �̸�� ������ ������Ʈ
	void	move();							// npc �̵�
	void	comparePrice();					// ���� ��
	void    wayPointSet();					// ���ߵǴ°� ����
	void	directionCheck();				// ���� �˻�
	void	chooseItem();					// ������ �̱�
	void	choosePt();

public:
	//============================ Get ===========================
	npcActionState getNPCActionState() { return _npcActionState; }
	npcEmotionState getNPCEmotionState() { return _npcEmotionState; }
	FloatRect getNPCRect() { return _rc; }
	int  getSelectPrice() { return _selectPrice; }
	int  getRndItem() { return _rndChoiceItem; }
	int  getOldRndItem() { return _oldRndChoiceItem; }
	bool getIsBuy() { return _isBuy; }
	bool getIsAway() { return _isAway; }
	bool getIsCount() { return _isCount; }
public:
	//============================ Set ===========================
	void setSettingPrice(int price) { _settingPrice = price; }
	void setRightPrice(int price) { _rightPrice = price; }
	void setIsCount(bool arg) { _isCount = arg; }
	void setIsAnotherPerson(int index, bool arg) { _isAnotherPerson[index] = arg; }
};

