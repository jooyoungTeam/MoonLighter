#pragma once
#include "singletonBase.h"
#include "item.h"

#define INVENSPACE 22				//�κ�ĭ��
#define GEARSPACE 6					//���ĭ��
#define SHOPSPACE 8					//����ĭ��
#define PRICESPACE 5				//���ݼ���

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
	wstring number;					//������ ���� ǥ�� string
	int count;						//������ ����
	int price;						//������ ����(������)
};

struct tagGear						//���â
{
	FloatRect rc;					//��� ĭ ��Ʈ
	item* item;						//���â�� ��� ������ Ŭ����
	wstring number;					//������ ���� ǥ�� string
	int count;						//������ ����
};

struct tagShop						//����
{
	FloatRect rc;					//������ ��� ��Ʈ
	item* item;						//�����̽��� ��� ������ Ŭ����
	wstring countNum;				//������ ���� ǥ�� string
	int count;						//������ ����
	int price;						//������ ������
	int totalPrice;					//�����̽� ��ü �ݾ�
};

struct tagSetPrice					//���� ���� â
{
	FloatRect rc;					//���� ���� ��Ʈ
	int price;						//�ԷµǴ� ����
};

class player;
class UI;
class itemManager;

class inventory : public singletonBase<inventory>
{
private:
	INVEN_STATE _state;					//��Ʈ�� �������� ���ڸ� ��������
	MIRROR_STATE _mirror;				//�̷� ����

	tagInven _inven[INVENSPACE];		//�κ�
	tagInven _selectItem;				//������ ������
	tagGear _gear[GEARSPACE];			//���ĭ
	tagShop _shop[SHOPSPACE];			//����ĭ
	tagSetPrice _firstPrice[PRICESPACE];//���ݼ���ĭ
	tagSetPrice _secondPrice[PRICESPACE];
	tagSetPrice _thirdPrice[PRICESPACE];
	tagSetPrice _fourthPrice[PRICESPACE];

	Image* _mirrorImg;					//�ſ��̹���
	Image* _saleImg;					//�Ǹ��̹���

	int _select;						//���� �κ� ��ȣ
	int _selectNumber;					//������ ĭ ��ȣ(�κ�)
	int _selectGearNumber;				//������ ĭ ��ȣ(���ĭ)
	int _selectShopNumber;				//������ ĭ ��ȣ(��)
	int _frameCount;					//�̷������ӿ�
	int _mirrorFrameX;					//�̷� ������X
	int _mirrorBallFrameX;				//�̷� �� �� ������X
	int _saleFrameX;					//�Ǹ� ������X
	int _count;							//�̷� ������
	int _selectPrice;					//���� ����
	int _gold;							//������

	bool _isSelect;						//������ �����ϴ� �� ��
	bool _isSale;						//������ �Ǹ��ϴ� �� ��
	bool _isSwap;						//�迭 �Ѿ��
	bool _isInven;						//�κ��丮 ������?
	bool _isSetPrice;					//���� ������ �Ŵ�

	player* _player;
	UI* _ui;
	itemManager* _itemMg;

public:
	inventory() {}
	~inventory() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void moveInven();										//�κ����� ���ƴٴϱ�
	void putItem(item* item);								//�κ��� ������ �ֱ�
	void selectItem();										//������ �����ϱ�
	void moveItem();										//������ �ű��
	void setPrice();										//���� �����ϱ�
	void closeInven();										//�κ� ������
	void useMirror();										//�̷� ����ϱ�
	void renderInven();										//�κ� ���¿� ���� ���� ����
	void draw();											//�̹��� ������ ������

public:
	int getGold() { return _gold; }							//������ ��������
	tagGear getPotion() { return _gear[4]; }				//���ĭ 4��°(����) ��������
	tagShop* getShowCase() { return _shop; }				//���� �迭 ��������
	INVEN_STATE getState() { return _state; }				//� �κ� �������� ��������
	bool getIsInven() { return _isInven; }

public:
	void setState(INVEN_STATE state) { _state = state; }	//� �κ� �������� �����ϱ�
	void setIsInven(bool arg) { _isInven = arg; }			//�κ� ���� ���� ���ϱ�

public:
	//�÷��̾� ������
	void getPlayerMemoryAddressLink(player* player) { _player = player; }
	//UI ������
	void getUIMemoryAddressLink(UI* ui) { _ui = ui; }
};