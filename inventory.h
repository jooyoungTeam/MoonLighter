#pragma once
#include "gameNode.h"
#include "item.h"

#define INVENSPACE 22					//�κ�ĭ��(����)
#define GEARSPACE 6						//���ĭ��(������)

enum class INVEN_STATE
{
	NOTE, BOX
};

enum class GEAR_KIND
{
	WEAPON1, WEAPON2, HELMET, TOP, SHOES, POTION
};

struct tagInven
{
	FloatRect rc;
	item* item;
	int count;
};

struct tagGear
{
	GEAR_KIND kind;
	FloatRect rc;
	item* item;
};

class inventory : public gameNode
{
private:
	INVEN_STATE _state;

	tagInven _inven[INVENSPACE];		//�κ�
	Image* _mirror;						//�ſ��̹���
	int _select;						//���� �κ� ��ȣ
	bool _isOpen;						//�κ� ������?

	tagGear _gear[GEARSPACE];			//���ĭ
	bool _isSwap;						//�Ѿ��

	int _frameCount;					//�̷������ӿ�
	int _mirrorFrameX;					//�̷�������X
	bool _isActive;						//�̷� ����?

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void putItem();											//�κ��� ������ �ֱ�
	void equipGear();										//��� �Ա�
	void draw();											//�̹��� ������ ������

public:
	bool getOpen() { return _isOpen; }						//�κ� �����ٴ� �� �� ��������
	INVEN_STATE getState() { return _state; }				//� �κ� �������� ��������

public:
	void setOpen(BOOL open = FALSE) { _isOpen = open; }		//�κ� �����ٴ� �� �� �����ϱ�
	void setState(INVEN_STATE state) { _state = state; }	//� �κ� �������� �����ϱ�
};