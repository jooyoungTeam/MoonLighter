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
	bool colAni;
};


class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	tagBullet _bullet;
	const char* _imageName;


public:
	virtual HRESULT init(const char* imageName);
	virtual void release();
	virtual void update();
	virtual void potRender();
	virtual void bossRender();

	virtual void fire(float x, float y, float angle, float speed);
	virtual void manyFire(float x, float y, float angle, float speed, float bulletNum);
	virtual void PFire(float x, float y, float angle, float speed);
	virtual void remove(int arr);

	vector<tagBullet> getVBullet() { return _vBullet; }

};

