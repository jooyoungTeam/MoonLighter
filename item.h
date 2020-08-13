#pragma once
#include "gameNode.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

enum class ITEMTYPE
{
	SLIME_RED, SLIME_BLUE, SLIME_YELLOW,
	VINE, WOOD, FABRIC, GOLEM_PIECES,
	BROKEN_SWORD, CRYSTAL_ENERGY, REINFORCED_STEEL, GOLEM_CORE,
	GOLEMKING_CRYSTAL, GOLEMKING_RECORD,
	POTION_S
};

class item : public gameNode
{
private:
	ITEMTYPE _type;
	FloatRect _rc;
	Image* _img;
	float _x, _y;
	float _shakeMaxY;
	float _shakeMinY;
	float _shake;
	int _itemIndex;
	int _limitCount;
	int _price;

	bool _isShake;
public:
	item() {}
	~item() {}

	HRESULT init(ITEMTYPE type, float x, float y);
	void render();			// �κ��丮�� ����
	void cameraRender();    // �ʵ�� ����
	void update();			// �κ��丮�� ������Ʈ
	void fieldUpdate();		// �ʵ�� ������Ʈ
	void release();
	
	void sort();


public:
	FloatRect getRc() { return _rc; }						//������ ��Ʈ ��������
	Image* getImg() { return _img; }						//������ �̹��� ��������
	int getIndex() { return _itemIndex; }					//������ �ε��� ��ȣ ��������
	int getLimit() { return _limitCount; }					//������ ���� �Ѱ�ġ ��������
	int getPrice() { return _price; }						//������ ���� ��������



	// ================== NPC =================
	void setItemPos(float x, float y) { _x = x; _y = y; }	// NPC �Ӹ����� ������ ���� ���� ��ġ ������ Setter
	void setShakeY(float y) { _shakeMaxY = y + 5; _shakeMinY = y; }
};

