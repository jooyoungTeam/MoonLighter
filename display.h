#pragma once
#include "gameNode.h"

class shopNPCManager;

class display : public gameNode
{
private:
	shopNPCManager* _npcM;
	int	_index;				// ���÷��� ��ȣ
	Vector2 _pos;			// ��ġ
	FloatRect _rc;			// ��Ʈ

	item* _it;				// ������
	int	  _settingPrice;		// �÷��̾� ���� ����
	int   _rightPrice;		// �˸��� ����
	int	  _count;			// ������ ����

	float _maxY;
	float _minY;
		  
	bool  _isActive;			// �����뿡 �������� �ֳ�?
	bool  _isPeople;			// �����뿡 ����� �ֳ�?

	bool  _direction;

public:
	HRESULT init(int index, Vector2 mPos, item* mIt, int mPrice, int mCount, bool mIsActive);
	void update();
	void render();
	void release();

	void itemMove();

public:
	void setMemoryAdressLinkNpcManager(shopNPCManager* npcM) { _npcM = npcM; }
};

