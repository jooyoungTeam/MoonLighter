#pragma once
#include "gameNode.h"
#include "enemyState.h"
#include "keyAniManager.h"



class enemy :
	public gameNode
{
private:

protected:
	int _index;
	enemyState* _state;
	ENEMYTYPE _type;

	string _mapName;


	FloatRect _rc;
	Image* _img;
	
	float _x, _y;
	float _width, _height;
	int _maxHP;
	animation* _motion;

	bool change;

public:

	virtual HRESULT init(int index, float x, float y, float width, float height, ENEMYTYPE type, string map);
	virtual void release();
	virtual void update();
	virtual void render();

	void ani();
	void test();

	void setChange(bool ch) { change = ch; }


};

