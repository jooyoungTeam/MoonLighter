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
	OBJECT 	           _currentSampleObject;    //현재 보고있는 오브젝트 넘버
	tagObject          _currentObject;          //선택한 오브젝트
	bool               _isSelectObject;         //잡고있는지
	RECT               _leftRightButton[2];
	tagSampleObject    _sampleObject[4];		//팔레트에 보여지는 오브젝트
	bool               _isDoorOpen;
	const char* str[OBJ_NONE] = { "objectHouse","objectArchitecture" ,"objectDoor","objectPlant","objectNPC",
	"objectSpa","objectDungeon1","objectDungeon2","object_rock1", "object_rock2","object_tile1",
	"object_tile2",	"object_tile3" };

public:
	objectManager() {}
	~objectManager() {}
public:
	HRESULT init();
	void objectRender();           //오브젝트만 랜더
	void currentObjectRender();    // 잡고있는 오브젝트 렌더
	void sampleObjectPageRender(); // 팔레트에 있는 오브젝트 렌더
	void update();
	void release();
public:
	void sampleObjectPage();
	// num1 던전1, num2 던전2, num3 스파
	void save(BUTTONTYPE type, int num);
	// num1 던전1, num2 던전2, num3 스파
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

