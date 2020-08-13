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
	float		shootX, shootY;			//�Ѿ� �߻�� ��ġ
	float		arrowDamage;			//ȭ�� ������
	bool		shoot;					//�߻��Ұ���
	int			count;

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
	
	void IsArrowShot(float x, float y, ARROWDIRECTION arrowDirection, float damage);
	void arrowMove();
	void playerRemoveArrow(int index);
};

