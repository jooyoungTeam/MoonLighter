#pragma once
#include "gameNode.h"
#include "stageManager.h"
class playGround : public gameNode
{
private:
	stageManager* _stageManager;


	// 마우스 관련 변수
	int _count;
	int _cursorFrameX;
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imageLoad();
	void cursor();
};

