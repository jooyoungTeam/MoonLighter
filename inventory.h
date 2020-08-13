#pragma once
#include "singletonBase.h"
#include "item.h"

#define INVENSPACE 22				//�κ�ĭ��
#define GEARSPACE 6					//���ĭ��
#define SHOPSPACE 4					//����ĭ��

enum class INVEN_STATE
{
	TEMP, NOTE, SHOP				//�κ��� ����� ����, ��ø �κ� ���, �� �κ� ���
};

enum class MIRROR_STATE
{
	STOP, STAY, ACTIVE				//�̷��� ��������, �̷��� �ӹ��� ����, �̷��� �����
};

struct tagInven						//�κ��丮
{
	FloatRect rc;					//�κ� ĭ ��Ʈ
	item* item;						//�κ��� ��� ������ Ŭ����
	int count;						//������ ����
	int price;						//������ ����(������)
	wstring number;					//������ ���� ǥ�� string
};

struct tagGear						//���â
{
	FloatRect rc;					//��� ĭ ��Ʈ
	item* item;						//���â�� ��� ������ Ŭ����
	int count;						//������ ����
	wstring number;					//������ ���� ǥ�� string
};

struct tagShop						//����
{
	FloatRect rc;					//������ ��� ��Ʈ
	item* item;						//�����̽��� ��� ������ Ŭ����
	int count;						//������ ����
	int price;						//������ ������
	wstring countNum;				//������ ���� ǥ�� string
	wstring priceNum;				//������ ������ ǥ�� string
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
	int _selectNumber;					//������ ĭ ��ȣ(�κ�)
	int _selectGearNumber;				//������ ĭ ��ȣ(���ĭ)
	int _selectShopNumber;				//������ ĭ ��ȣ(��)
	bool _isSelect;						//������ �����ϴ� �� ��
	bool _isSale;						//������ �Ǹ��ϴ� �� ��
	bool _isInven;

	tagGear _gear[GEARSPACE];			//���ĭ
	tagShop _shop[SHOPSPACE];			//����ĭ
	bool _isSwap;						//�Ѿ��

	MIRROR_STATE _mirror;				//�̷� ����
	int _frameCount;					//�̷������ӿ�
	int _mirrorFrameX;					//�̷� ������X
	int _mirrorBallFrameX;				//�̷� �� �� ������X
	int _saleFrameX;					//�Ǹ� ������X
	int _count;							//�̷� ������

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
	void selectInvenItem();									//������ �����ϱ�
	void moveInvenItem();									//������ �ű��
	void closeInven();										//�κ� ������
	void useMirror();										//�̷� ����ϱ�
	void draw();											//�̹��� ������ ������

public:
	int getGold() { return _gold; }							//������ ��������
	tagGear getPotion() { return _gear[4]; }				//���ĭ 4��°(����) ��������
	tagShop* getShowCase() { return _shop; }				//���� �迭 ��������
	INVEN_STATE getState() { return _state; }				//� �κ� �������� ��������
	bool getIsInven() { return _isInven; }

public:
	void setState(INVEN_STATE state) { _state = state; }	//� �κ� �������� �����ϱ�
	void setIsInven(bool arg) { _isInven = arg; }

public:
	//�÷��̾� ������
	void getPlayerMemoryAddressLink(player* player) { _player = player; }
	//UI ������
	void getUIMemoryAddressLink(UI* ui) { _ui = ui; }
};