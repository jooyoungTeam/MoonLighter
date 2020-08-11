#pragma once
#include "gameNode.h"
#include "enemyState.h"
#include "aStar.h"

class enemy : public gameNode
{
private:

protected:
	//스테이트 패턴
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

	
	animation* _motion;	//애니메이션
	
	Image* _img;		//에너미 이미지
	FloatRect _rc;		//에너미 렉트

	int _maxHP;			//에너미 HP
	int _index;			//키애니에 사용하는 인덱스
	int _attackDelay;	//공격 딜레이용

	float _x, _y;		//에너미 중심
	float _width, _height;//크기
	float _pX, _pY;		//플레이어 중심	
	float _angle;		//골렘 앵글
	float _moveAngle;

	bool _isAttack;		//공격하는지?
	bool _isSlimeAttack;

	int _rndX;
	int _rndY;



public:

	virtual HRESULT init(int index, float x, float y, float width, float height, ENEMYTYPE type);
	virtual void release();
	virtual void update();
	virtual void render();
	void playerCheck(float x, float y); //나중에 여기에 렉트 추가해
	void ani();					//이미지 애니 다 넣은곳
	virtual void attack();		//에너미 공격 넣을 곳
	virtual void enemyMove();	// 움직임 넣을 곳
	virtual void set();			//상속받아서 초기화 할 곳
	virtual void enemyWay();	//방향 결정
	virtual void move();		//astar
	virtual void directionCheck();//골렘 방향 돌려주는거

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

