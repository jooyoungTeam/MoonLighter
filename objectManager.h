#pragma once
#include "gameNode.h"
enum OBJECT
{
	OBJ_HOUSE, OBJ_ARCHITECTURE, OBJ_DOOR, OBJ_PLANT, OBJ_NPC, OBJ_SPA, OBJ_DUN1, OBJ_DUN2,
	OBJ_NONE,
};

struct tagSampleObject
{
	RECT    rc;
	int     objFrameX;
	int     objFrameY;
};

struct tagObject
{
	OBJECT   type;
	RECT     rc;
	bool     isFrameRender;
	float    scale;
	int      frameX;
	int      count;
	int      imgNumber;
};

class objectManager : public gameNode
{
private:
	vector<tagObject>  _vObject;


	OBJECT 	           _currentSampleObject;    //���� �����ִ� ������Ʈ �ѹ�
	tagObject          _currentObject;          //������ ������Ʈ
	bool               _isSelectObject;         //����ִ���
	RECT               _leftRightButton[2];
	tagSampleObject    _sampleObject[4];		//�ȷ�Ʈ�� �������� ������Ʈ

public:
	objectManager() {}
	~objectManager() {}
public:
	HRESULT init();
	void objectRender();           //������Ʈ�� ����
	void currentObjectRender();    // ����ִ� ������Ʈ ����
	void sampleObjectPageRender(); // �ȷ�Ʈ�� �ִ� ������Ʈ ����
	void update();
	void release();
public:
	void sampleObjectPage();
	void save(BUTTONTYPE type);
	void load(BUTTONTYPE type);
	void setObject(POINT pt);
	void selectObject();
	void eraseObject(POINT pt);
	Image* findImg(OBJECT type, int imgNum);
public:
	vector<tagObject> getVObject() { return _vObject; }
};

