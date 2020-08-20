#pragma once
#include "gameNode.h"
#include <vector>

enum class ARROWDIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

struct tagArrow
{
	Image*  	arrowImage;
	FloatRect	rc;
	float		x, y;
	float		speed;
	float		angle;
	float		gravity;
	float		power;
	float		shootX, shootY;			//총알 발사된 위치
	float		arrowDamage;			//화살 데미지
	bool		shoot;					//발사할건지
	int			count;
	bool        isPowerShot;
	bool        isActive;
	ARROWDIRECTION arrowDirection;
};

class arrow : public gameNode
{
private:
	vector<tagArrow>				_vArrow;
	vector<tagArrow>::iterator		_viArrow;
public:
	arrow();
	~arrow();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	void IsArrowShot(float x, float y, ARROWDIRECTION arrowDirection, float damage, bool isPower);
	void arrowMove();
	void playerRemoveArrow(int index);
	void arrowIsActive(int index, bool active);

	vector<tagArrow> getVArrow()	{ return _vArrow; }

};

