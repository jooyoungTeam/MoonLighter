#pragma once
#include "gameNode.h"
#include "item.h"

#define INVENSPACE 22					//�κ�ĭ��(����)
#define GEARSPACE 6						//���ĭ��(������)

struct tagInven
{
	FloatRect rc;
	item* item;
	int count;
};

class inventory : public gameNode
{
private:
	tagInven _inven[INVENSPACE];		//�κ�
	Image* _mirror;						//�ſ��̹���
	int _select;						//���� �κ� ��ȣ
	bool _isOpen;						//�κ� ������?

	int _frameCount;
	int _mirrorFrameX;
	bool _isActive;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void putItem();											//�κ��� ������ �ֱ�
	void draw();											//�̹��� ������ ������

public:
	bool getOpen() { return _isOpen; }						//�κ� �����ٴ� �� �� ��������

public:
	void setOpen(BOOL open = FALSE) { _isOpen = open; }		//�κ� �����ٴ� �� �� �����ϱ�
};