#pragma once
#include "gameNode.h"
enum OBJECT
{
	OBJ_HOUSE, OBJ_ARCHITECTURE, OBJ_DOOR, OBJ_PLANT, OBJ_NPC, OBJ_SPA, OBJ_DUN1, OBJ_DUN2,
	OBJ_NONE,
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
public:
	objectManager() {}
	~objectManager() {}
public:
	HRESULT init();
	void render();
	void update();
	void release();
public:
	void save(BUTTONTYPE type);
	void load(BUTTONTYPE type);
	void setObject(POINT pt,tagObject object);
	void selectObject(tagObject& object, OBJECT type, int imgNumber);
	void eraseObject(int arrNum) { _vObject.erase(_vObject.begin() + arrNum); }	
	Image* findImg(OBJECT type, int imgNum);
};

