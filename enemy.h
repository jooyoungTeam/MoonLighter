#pragma once
#include "gameNode.h"
#include "enemyState.h"
#include "aStar.h"

struct tagBar
{
	float x, y;
	float width;
	FloatRect back;
	FloatRect middle;
	FloatRect front;
};
enum BOSS_ANI
{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX
};


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
	BOSS_ANI _bossAni;

	tagBar _bar;
	
	animation* _motion;	//애니메이션
	
	Image* _img;		//에너미 이미지
	Image* _shadow;		//그림자 이미지
	Image* _backBar;	//체력바 이미지
	Image* _middleBar;
	Image* _frontBar;
	FloatRect _rc;		//에너미 렉트
	FloatRect _pRc;		//플레이어 렉트
	FloatRect _attackRc;//공격렉트

	int _maxHP, _curHP, _saveHP;			//에너미 HP
	int _index;			//키애니에 사용하는 인덱스
	int _attackDelay;	//공격 딜레이용
	int _middleBarCut;	//미들바 점점 줄어들게...
	int _rndX;			//astar 랜덤 값 준거
	int _rndY;			//이것또한..
	int _hitCount;		//맞을때 반짝
	int _bossHitCount;
	int _isHitCount;	//isHit의 카운트임


	float _x, _y, _z;		//에너미 중심
	float _width, _height;//크기
	float _pX, _pY;		//플레이어 중심	
	float _angle;		//골렘 앵글
	float _moveAngle;	//astar앵글
	float _attackAngle;	//슬라임 달려가는 공격 앵글 넣어주려구
	float _scale;		//에너미 그림마다 스케일 주랴구
	float _speed;		//에너미 움직이는 스피드
	float _barAlpha;	//맞을때만 잠깐 나오려구


	bool _isAttack;		//공격하는지?
	bool _isCol;
	bool _onceAni;		//애니 스타트 하는거 한 번만 들어오게..
	bool _realDead;		//애니 다 하구 에너미 없어지게 하는거
	bool _isHit;		//맞음
	bool _isBossPull;	//보스 끌어당김
	bool _isBossPush;	//보스 밈
	bool _isRockBottom;
		


public:

	virtual HRESULT init(int index, float x, float y, float width, float height, ENEMYTYPE type);
	virtual void release();
	virtual void update();
	virtual void render();
	void playerCheck(float x, float y, FloatRect rc); //나중에 여기에 렉트 추가해
	virtual void attack() {}	//에너미 공격 넣을 곳
	virtual void enemyMove() {}	// 움직임 넣을 곳
	virtual void dead() {}		//에너미 죽는거
	virtual void set() {}		//상속받아서 초기화 할 곳
	virtual void enemyWay();	//방향 결정
	virtual void move();		//astar
	virtual void hitMove();		//힛상태이면 반대로 움직이게
	virtual void directionCheck() {}//골렘 방향 돌려주는거
	virtual void enemyHit() {}	//골렘 힛으로 바꿔주는거
	virtual void setShadow() {}	//골렘 그림자 캐릭터마다 위치 다르게 해주려고 
	void setBar();				//에너미마다 체력바 위치 정해줌
	void ani();					//이미지 애니 다 넣은곳
	void checkBoolCount();		//불값이랑 카운트 체크용

	void setGauge(float curHP, float maxHP);	//체력바

	//---------------------------------set-----------------------------------
	void setState(enemyState* state) { this->_state = state; }
	void setMotion(Image* img, animation* ani) { _img = img; _motion->stop();  _motion = ani; _motion->start(); }
	void setPotDirection(POTDIR dir) { _potDir = dir; }
	void setBossAni(BOSS_ANI ani) { _bossAni = ani; }

	void setAttackRect(float x, float y, float width, float height) { _attackRc = RectMakePivot(Vector2(x, y), Vector2(width, height), Pivot::Center); }
	void setY(float y) { _y = y; }
	void setAttackAngle(float angle) { _attackAngle = angle; }
	void setScale(float s) { _scale = s; }
	void setBarAlpha(float alpha) { _barAlpha = alpha; }


	void setAttackDelay(int delay) { _attackDelay = delay; }
	void setHP(int hp = 30) { _curHP -= hp; }
	void setSaveHP(int hp) { _saveHP = hp; }


	void setIsAttack(bool attack) { _isAttack = attack; }
	void setIsCol(bool col) { _isCol = col; }
	void setOnceAni(bool ani) { _onceAni = ani; }
	void setRealDead(bool d) { _realDead = d; }
	void setIsHit(bool hit) { _isHit = hit; }
	void setIsPull(bool pull) { _isBossPull = pull; }
	void setIsPush(bool push) { _isBossPush = push; }
	void setIsRockBottom(bool bottom) { _isRockBottom = bottom; }

	void setEnemyAttack(int hp = 3)
	{
		if (_state != _hit && _state != _dead)
		{
			_saveHP = _bar.width;
			if (_type != ENEMY_BOSS)
			{
				hp = 30;
				_isHit = true;
				_barAlpha = 1.0f;
			}
			_curHP -= hp;
			if (_type == ENEMY_BOSS)
			{
				if (_state == _idle)
				{
					_bossHitCount++;
				}
				if (_bossHitCount > 2)
				{
					_bossHitCount = 0;
					_state = _hit;
				}
			}
		}
		if (_curHP <= 0)
		{
			_onceAni = true;
			if (_type == ENEMY_BOSS)
			{
				if (_state != _dead)
				{
					_bossAni = ONE;
					_state = _dead;
				}
			}
		}
	}


	//---------------------------------get-----------------------------------


	float getX() { return _x; }
	float getY() { return _y; }
	float getWidth() { return _width; }
	float getHeight() { return _height; }
	float getPX() { return _pX;}
	float getPY() { return _pY; }
	float getMoveAngle() { return _moveAngle; }
	float getAttackAngle() { return _attackAngle; }

	int getIndex() { return _index; }
	int getAttackDelay() { return _attackDelay; }
	int getCurHP() { return _curHP; }

	bool getIsAttack() { return _isAttack; }
	bool getIsCol() { return _isCol; }
	bool getRealDead() { return _realDead; }
	bool getIsHit() { return _isHit; }
	bool getIsPull() { return _isBossPull; }
	bool getIsPush() { return _isBossPush; }
	bool getIsRockBottom() { return _isRockBottom; }

	tagBar getBar() { return _bar; }
	FloatRect getEnemyAttackRect() { return _attackRc; }
	FloatRect getEnemyRect() { return _rc; }
	FloatRect getPlayerRect() { return _pRc; }
	animation* getAni() { return _motion; }

	GOLEMDIR getGolDriection() { return _golemDir; }
	POTDIR getPotDirection() { return _potDir; }
	ENEMYTYPE getEnemyType() { return _type; }

	enemyState* getState() { return _state; }
	enemyState* getIdle() { return _idle; }			
	enemyState* getMove() { return _move; }
	enemyState* getAttack() { return _attack; }
	enemyState* getHit() { return _hit; }
	enemyState* getDead() { return _dead; }


};

