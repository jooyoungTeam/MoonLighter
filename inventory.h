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

//�κ��丮
struct tagInven						
{
	FloatRect rc;					//�κ� ĭ ��Ʈ
	item* item;						//�κ��� ��� ������ Ŭ����
	wstring number;					//������ ���� ǥ�� string
	int count;						//������ ����
	int price;						//������ ����(������)
	bool isFull;
};

//���â
struct tagGear						
{
	FloatRect rc;					//��� ĭ ��Ʈ
	item* item;						//���â�� ��� ������ Ŭ����
	wstring number;					//������ ���� ǥ�� string
	int count;						//������ ����
};

//����
struct tagShop						
{
	FloatRect rc;					//������ ��� ��Ʈ
	item* item;						//�����̽��� ��� ������ Ŭ����
	wstring countNum;				//������ ���� ǥ�� string
	int count;						//������ ����
	int price;						//������ ������
	int totalPrice;					//�������� ��ü �ݾ�
	int originalPrice;				//������ ���� ��ü �ݾ�
	bool isPeople;
};

//���� ���� â
struct tagSetPrice					
{
	FloatRect rc;					//���� ���� ��Ʈ
	int count;						//�ԷµǴ� ����
};

//���� �����
struct tagSavePrice					
{
	int index;						//������ ��ȣ
	int price;						//������ ����
};

class player;
class UI;

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
	int _selectCount;					//���� ����
	int _gold;							//������

	bool _isSelect;						//������ �����ϴ� �� ��
	bool _isSale;						//������ �Ǹ��ϴ� �� ��(�̷����)
	bool _isSwap;						//�迭 �Ѿ��
	bool _isSetPrice;					//���� ������ �Ŵ�
	bool _isInven;						//�κ��丮 ������?

	vector<tagSavePrice> _vPrice;		//������ ���� ������ ����
	vector<ITEMTYPE> _vType;			//������ Ÿ�� ������ ����

	player* _player;
	UI* _ui;

public:
	inventory() {}
	~inventory() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void moveInven();										//�κ����� ���ƴٴϱ�
	bool putItem(item* item);								//�κ��� ������ �ֱ�
	int fullInven();										//�κ� ���� á���� Ȯ���ϱ�

	// ����µ� �ʿ��� ������ �ε���(index), ����(count), �ݾ�(gold)
	void makePotion(int selectPotionIndex, int index, int count, int gold);		

	void selectItem();										//������ �����ϱ�
	void moveItem();										//������ �ű��

	void renderInven();										//�κ� ���¿� ���� ���� ����
	void closeInven();										//�κ� ������
	void popInven();										//�κ� ����
	void putType();

	void setCount(tagSetPrice p[PRICESPACE], wstring d);	//���� �����ϱ�
	void setPrice(tagSetPrice p[PRICESPACE], int s);		//���� ����ϱ�
	void savePrice(int select);								//���� �����ϱ�
	void loadPrice(tagSetPrice p[PRICESPACE], int s);		//���� �ҷ�����

	void useMirror();										//�̷� ����ϱ�
	void draw();											//�̹��� ������ ������

public:
	int getGold() { return _gold; }							//������ ��������
	tagInven* getInven() { return _inven; }
	tagGear getPotion() { return _gear[4]; }				//���ĭ 4��°(����) ��������
	tagShop* getShowCase() { return _shop; }				//���� �迭 ��������
	INVEN_STATE getState() { return _state; }				//� �κ� �������� ��������
	bool getIsInven() { return _isInven; }
	vector<ITEMTYPE> getVType() { return _vType; }

public:
	void setState(INVEN_STATE state) { _state = state; }	//� �κ� �������� �����ϱ�
	void setIsInven(bool arg) { _isInven = arg; }			//�κ� ���� ���� ���ϱ�
	void resetShowCase(int index)							//������ �ȸ� �� �����̽� ����
	{ 
		_shop[index].count = 0;
		_shop[index].countNum = L"";
		_shop[index].item = NULL;
		_shop[index].originalPrice = 0;
		_shop[index].price = 0;
		_shop[index].totalPrice = 0;
	}					

	int countOfPotion()										//���� ���� ���� �Լ�
	{
		for (int i = 0; i < INVENSPACE; i++)
		{
			if (_inven[i].item == nullptr) continue;

			int count;

			if (_inven[i].item->getIndex() > 1000)
			{
				count++;
			}
			return count;
		}
	}

public:
	//�÷��̾� ������
	void getPlayerMemoryAddressLink(player* player) { _player = player; }
	//UI ������
	void getUIMemoryAddressLink(UI* ui) { _ui = ui; }
};