#pragma once
#include "gameNode.h"
#include "item.h"

#define INVENSPACE 22					//�κ�ĭ��(����)
#define GEARSPACE 6						//���ĭ��(������)

enum class INVEN_STATE
{
	NOTE, BOX
};

enum class MIRROR_STATE
{
	STOP, STAY, ACTIVE
};

enum class GEAR_KIND
{
	WEAPON1, WEAPON2, HELMET, TOP, SHOES, POTION
};

struct tagInven
{
	FloatRect rc;
	item* item;
	wstring number;
	int count;
};

struct tagGear
{
	GEAR_KIND kind;
	FloatRect rc;
	item* item;
	int count;
};

class inventory : public gameNode
{
private:
	INVEN_STATE _state;					//��Ʈ�� �������� ���ڸ� ��������

	tagInven _inven[INVENSPACE];		//�κ�
	tagInven _selectItem;				//������ ������
	Image* _mirrorImg;					//�ſ��̹���
	int _select;						//���� �κ� ��ȣ
	int _count;							//�̷� ������
	bool _isOpen;						//�κ� ������?
	bool _isSelect;						//������ �����ϴ� �� ��

	tagGear _gear[GEARSPACE];			//���ĭ
	bool _isSwap;						//�Ѿ��

	MIRROR_STATE _mirror;				//�̷� ����
	int _frameCount;					//�̷������ӿ�
	int _mirrorFrameX;					//�̷�������X

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void putItem(item* item);								//�κ��� ������ �ֱ�
	void moveItem();										//�κ����� ������ �ű��
	void equipGear();										//��� �Ա�
	void useMirror();										//�̷� ����ϱ�
	void draw();											//�̹��� ������ ������

public:
	bool getOpen() { return _isOpen; }						//�κ� �����ٴ� �� �� ��������
	INVEN_STATE getState() { return _state; }				//� �κ� �������� ��������

public:
	void setOpen(BOOL open = FALSE) { _isOpen = open; }		//�κ� �����ٴ� �� �� �����ϱ�
	void setState(INVEN_STATE state) { _state = state; }	//� �κ� �������� �����ϱ�
};