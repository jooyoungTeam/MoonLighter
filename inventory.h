#pragma once
#include "gameNode.h"
#include "item.h"

#define INVENSPACE 22					//�κ�ĭ��(����)
#define GEARSPACE 6						//���ĭ��(������)

enum class INVEN_STATE
{
	NOTE, SHOP, BOX
};

enum class MIRROR_STATE
{
	STOP, STAY, ACTIVE
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
	Image* img;
	FloatRect rc;
	item* item;
	wstring number;
	int count;
};

class player;

class inventory : public gameNode
{
private:
	INVEN_STATE _state;					//��Ʈ�� �������� ���ڸ� ��������

	tagInven _inven[INVENSPACE];		//�κ�
	tagInven _selectItem;				//������ ������
	Image* _mirrorImg;					//�ſ��̹���
	int _select;						//���� �κ� ��ȣ
	int _selectNumber;					//�������� ���� �κ� ��ȣ
	int _count;							//�̷� ������
	bool _isOpen;						//�κ� ������?
	bool _isSelect;						//������ �����ϴ� �� ��

	tagGear _gear[GEARSPACE];			//���ĭ
	bool _isSwap;						//�Ѿ��

	MIRROR_STATE _mirror;				//�̷� ����
	int _frameCount;					//�̷������ӿ�
	int _mirrorFrameX;					//�̷�������X

	player* _player;

public:
	inventory() {}
	~inventory() {}

	HRESULT init();
	void render();
	void update();
	void release();

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

public:
	//�÷��̾� ������
	void getPlayerMemoryAddressLik(player* player) { _player = player; }
};