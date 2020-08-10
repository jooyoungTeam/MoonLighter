#pragma once
#include "gameNode.h"
#include "enemyState.h"
#include "aStar.h"

class enemy : public gameNode
{
private:

protected:
	enemyState* _state;
	enemyState* _idle;
	enemyState* _move;
	enemyState* _attack;
	enemyState* _hit;
	enemyState* _dead;
	aStar* _aStar;

	ENEMYTYPE _type;
	GOLEMDIR _golemDir;
	POTDIR _potDir;

	
	animation* _motion;
	
	Image* _img;
	FloatRect _rc;

	int _maxHP;
	int _index;		//키애니에 사용하는 인덱스
	int _attackDelay;

	float _x, _y;
	float _width, _height;
	float _pX, _pY;
	float _angle;

	bool _isAttack;





public:

	virtual HRESULT init(int index, float x, float y, float width, float height, ENEMYTYPE type);
	virtual void release();
	virtual void update();
	virtual void render();
	void playerCheck(float x, float y); //나중에 여기에 렉트 추가해
	void ani();
	virtual void attack();
	virtual void enemyMove();
	virtual void set();
	virtual void enemyWay();
	virtual void move();

	//---------------------------------set-----------------------------------
	void setState(enemyState* state) { this->_state = state; }
	void setMotion(Image* img, animation* ani) { _img = img; _motion = ani; _motion->start(); }
	void setPotDirection(POTDIR dir) { _potDir = dir; }

	void setIsAttack(bool attack) { _isAttack = attack; }
	void setAttackDelay(int delay) { _attackDelay = delay; }

	//---------------------------------get-----------------------------------


	float getX() { return _x; }
	float getY() { return _y; }
	float getPX() { return _pX;}
	float getPY() { return _pY; }

	int getIndex() { return _index; }
	int getAttackDelay() { return _attackDelay; }

	bool getIsAttack() { return _isAttack; }

	animation* getAni() { return _motion; }

	GOLEMDIR getGolDriection() { return _golemDir; }
	POTDIR getPotDirection() { return _potDir; }
	ENEMYTYPE getEnemyType() { return _type; }

	enemyState* getIdle() { return _idle; }			
	enemyState* getMove() { return _move; }
	enemyState* getAttack() { return _attack; }
	enemyState* getHit() { return _hit; }
	enemyState* getDead() { return _dead; }


};

