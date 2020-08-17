#pragma once
#include "gameNode.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

enum class ITEMTYPE
{
	SLIME_RED, SLIME_BLUE, SLIME_YELLOW,
	//VINE, WOOD,
	CRYSTAL_ENERGY, REINFORCED_STEEL,
	BROKEN_SWORD, GOLEM_CORE,
	FABRIC, GOLEM_PIECES,
	GOLEMKING_CRYSTAL, GOLEMKING_RECORD,
	POTION_S
};

enum class ITEMBUNDLE
{
	SLIME_RED,
	SLIME_BLUE,
	SLIME_YELLOW,
	GOLEM_KNIGHT,
	GOLEM_POT,
	GOLEM_KING
};

class item : public gameNode
{
private:
	ITEMTYPE _type;						//������ Ÿ��
	ITEMBUNDLE _bundle;					//���ʹ̿� ���� ����
	FloatRect _rc;						//������ ��Ʈ
	Image* _img;						//������ �̹���
	float _x, _y;						//������ ��Ʈ x, y ��ǥ
	float _shakeMaxY;					//���� ������ �սǵս� �ִ� y��ǥ
	float _shakeMinY;					//���� ������ �սǵս� �ּ� y��ǥ
	float _shake;						//�սǵս� ����
	float _endX, _endY;					//������ ���� ����� ��ǥ x, y ��ǥ
	float _jumpPower;					//������ ����� �����Ŀ�
	float _gravity;						//����� �߷°�
	int _itemIndex;						//������ ������ȣ
	int _limitCount;					//������ ��� ���� �� �ִ� �ִ� ����
	int _price;							//������ ����
	int _count;							//������ �������� ��󳻴� ����

	bool _isShake;						//�սǵս�
	bool _isDrop;						//������ ���
public:
	item() {}
	~item() {}

	HRESULT init(ITEMBUNDLE bundle, float x, float y, float endX, float endY);
	HRESULT init(ITEMTYPE type);
	void render();				//�κ��丮�� ����
	void cameraRender();	    //�ʵ�� ����
	void update();				//�κ��丮�� ������Ʈ
	void fieldUpdate();			//�ʵ�� ������Ʈ
	void move();				//������ ����� ������
	void follow(FloatRect rc);	//�÷��̾� �Ѿƴٴ� �Լ�
	void release();
	
	void category();			//������ ������ ���� ���� ����
	void setBundle();			//���ʹ� ������ ���� ������ ����


public:
	ITEMTYPE getType() { return _type; }					//������ Ÿ�� ��������
	FloatRect getRc() { return _rc; }						//������ ��Ʈ ��������
	Image* getImg() { return _img; }						//������ �̹��� ��������
	int getIndex() { return _itemIndex; }					//������ �ε��� ��ȣ ��������
	int getLimit() { return _limitCount; }					//������ ���� �Ѱ�ġ ��������
	int getPrice() { return _price; }						//������ ���� ��������

public:
	// ================== NPC =================
	void setItemPos(float x, float y) { _x = x; _y = y; }	// NPC �Ӹ����� ������ ���� ���� ��ġ ������ Setter
	void setShakeY(float y) { _shakeMaxY = y + 5; _shakeMinY = y; }
};

