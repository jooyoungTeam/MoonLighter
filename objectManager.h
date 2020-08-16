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


	OBJECT 	           _currentSampleObject;    //현재 보고있는 오브젝트 넘버
	tagObject          _currentObject;          //선택한 오브젝트
	bool               _isSelectObject;         //잡고있는지
	RECT               _leftRightButton[2];
	tagSampleObject    _sampleObject[4];		//팔레트에 보여지는 오브젝트

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
	void save(BUTTONTYPE type);
	void load(BUTTONTYPE type);
	void setObject(POINT pt);
	void selectObject();
	void eraseObject(POINT pt);
	Image* findImg(OBJECT type, int imgNum);
public:
	vector<tagObject> getVObject() { return _vObject; }
};

