#pragma once
#include "gameNode.h"

struct tagBullet
{
	Image* img;
	FloatRect rc;
	float x, y;
	float sX, sY;
	float angle;
	float speed;
	bool isFire;
	int count;
	int index;
	int delay;
};


class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(float x, float y, float angle, float speed);
	virtual void remove(int arr);
};

