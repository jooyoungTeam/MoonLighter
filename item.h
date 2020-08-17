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
	ITEMTYPE _type;
	ITEMBUNDLE _bundle;
	FloatRect _rc;
	Image* _img;
	float _x, _y;
	float _shakeMaxY;
	float _shakeMinY;
	float _shake;
	float _endX, _endY;
	float _jumpPower;
	float _gravity;
	int _itemIndex;
	int _limitCount;
	int _price;
	int _count;

	bool _isShake;
	bool _isDrop;
public:
	item() {}
	~item() {}

	HRESULT init(ITEMBUNDLE bundle, float x, float y, float endX, float endY);
	HRESULT init(ITEMTYPE type);
	void render();			// �κ��丮�� ����
	void cameraRender();    // �ʵ�� ����
	void update();			// �κ��丮�� ������Ʈ
	void fieldUpdate();		// �ʵ�� ������Ʈ
	void move();
	void release();
	
	void category();			//������ ������ ���� ���� ����
	void setBundle();


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
	// ================== �����۸Ŵ��� =================
	void setItemType(ITEMTYPE type) { _type = type; }
};

