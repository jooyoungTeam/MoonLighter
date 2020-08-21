#pragma once
#include "gameNode.h"
enum OBJECT
{
	OBJ_HOUSE, OBJ_ARCHITECTURE, OBJ_DOOR, OBJ_PLANT, OBJ_NPC,
	OBJ_SPA, OBJ_DUN1, OBJ_DUN2, OBJ_ROCK1, OBJ_ROCK2, OBJ_TILE1,
	OBJ_TILE2, OBJ_TILE3,
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
	bool               _isDoorOpen;
	const char* str[OBJ_NONE] = { "objectHouse","objectArchitecture" ,"objectDoor","objectPlant","objectNPC",
	"objectSpa","objectDungeon1","objectDungeon2","object_rock1", "object_rock2","object_tile1",
	"object_tile2",	"object_tile3" };

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
	// num1 ����1, num2 ����2, num3 ����
	void save(BUTTONTYPE type, int num);
	// num1 ����1, num2 ����2, num3 ����
	void load(BUTTONTYPE type, int num);
	void setObject(POINT pt);
	void selectObject();
	void eraseObject(POINT pt);
	Image* findImg(OBJECT type, int imgNum);
public:
	bool isPlayerSpaIn(POINT playerPos);

public:
	vector<tagObject> getVObject() { return _vObject; }
	void setIsDoorOpen(bool open) { _isDoorOpen = open; }
	bool GetIsDoorOpen() { return _isDoorOpen; }
};

