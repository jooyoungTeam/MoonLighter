#pragma once
#include "gameNode.h"
#include "enemyState.h"



class enemy : public gameNode
{
private:

protected:
	int _index;		//키애니에 사용하는 인덱스
	enemyState* _state;
	ENEMYTYPE _type;

	string _mapName;


	FloatRect _rc;
	Image* _img;
	
	float _x, _y;
	float _width, _height;
	int _maxHP;
	animation* _motion;

	float _pX, _pY;
	RECT _pRc;

	bool change;	//test용 나중에 지우기

	enemyState* _idle;
	enemyState* _move;
	enemyState* _attack;
	enemyState* _hit;
	enemyState* _dead;


public:

	virtual HRESULT init(int index, float x, float y, float width, float height, ENEMYTYPE type, string map);
	virtual void release();
	virtual void update();
	virtual void render();
	void playerCheck(float x, float y); //나중에 여기에 렉트 추가해
	void ani();
	void test();
	virtual void attack();
	virtual void enemyMove();
	virtual void set();

	//---------------------------------set-----------------------------------
	void setChange(bool ch) { change = ch; }
	void setMotion(Image* img, animation* ani) { _img = img; _motion = ani; _motion->isPlay(); }
	void setState(enemyState* state) { this->_state = state; }

	//---------------------------------get-----------------------------------
	float getX() { return _x; }
	float getY() { return _y; }
	float getPX() { return _pX;}
	float getPY() { return _pY; }


	enemyState* getIdle() { return _idle; }			
	enemyState* getMove() { return _move; }
	enemyState* getAttack() { return _attack; }
	enemyState* getHit() { return _hit; }
	enemyState* getDead() { return _dead; }


};

