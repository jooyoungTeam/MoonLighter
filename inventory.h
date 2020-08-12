#pragma once
#include "singletonBase.h"
#include "item.h"

#define INVENSPACE 22					//�κ�ĭ��(����)
#define GEARSPACE 6						//���ĭ��(������)
#define SHOPSPACE 4						//����ĭ��

enum class INVEN_STATE
{
	NOTE, SHOP
};

enum class MIRROR_STATE
{
	STOP, STAY, ACTIVE
};

struct tagInven
{
	FloatRect rc;
	item* item;
	int count;
	wstring number;
};

struct tagGear
{
	Image* img;
	FloatRect rc;
	item* item;
	int count;
	wstring number;
};

struct tagShop
{
	FloatRect rc;
	item* item;
	int count;
	int price;
	wstring countNum;
	wstring priceNum;
};

class player;
class UI;

class inventory : public singletonBase<inventory>
{
private:
	INVEN_STATE _state;					//��Ʈ�� �������� ���ڸ� ��������

	tagInven _inven[INVENSPACE];		//�κ�
	tagInven _selectItem;				//������ ������
	Image* _mirrorImg;					//�ſ��̹���
	Image* _saleImg;					//�Ǹ��̹���
	int _select;						//���� �κ� ��ȣ
	int _selectNumber;					//�������� ���� �κ� ��ȣ
	int _count;							//�̷� ������
	bool _isSelect;						//������ �����ϴ� �� ��
	bool _isSale;						//������ �Ǹ��ϴ� �� ��

	tagGear _gear[GEARSPACE];			//���ĭ
	tagShop _shop[SHOPSPACE];			//����ĭ
	bool _isSwap;						//�Ѿ��

	MIRROR_STATE _mirror;				//�̷� ����
	int _frameCount;					//�̷������ӿ�
	int _mirrorFrameX;					//�̷� ������X
	int _mirrorBallFrameX;				//�̷� �� �� ������X
	int _saleFrameX;					//�Ǹ� ������X

	int _gold;							//������

	player* _player;
	UI* _ui;

public:
	inventory() {}
	~inventory() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void putItem(item* item);								//�κ��� ������ �ֱ�
	void moveItem();										//�κ����� ������ �ű��
	void useMirror();										//�̷� ����ϱ�
	void draw();											//�̹��� ������ ������

public:
	int getGold() { return _gold; }							//������ ��������
	tagGear getPotion() { return _gear[4]; }				//���ĭ 4��°(����) ��������
	INVEN_STATE getState() { return _state; }				//� �κ� �������� ��������

public:
	void setSale(BOOL sale = FALSE) { _isSale = sale; }		//�Ǹ��ϴ� �� �� �����ϱ�
	void setState(INVEN_STATE state) { _state = state; }	//� �κ� �������� �����ϱ�

public:
	//�÷��̾� ������
	void getPlayerMemoryAddressLink(player* player) { _player = player; }
	//UI ������
	void getUIMemoryAddressLink(UI* ui) { _ui = ui; }
	
	tagShop* getShowCase() { return _shop; }
};