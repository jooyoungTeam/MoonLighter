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
	//������Ʈ ����
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
	
	animation* _motion;	//�ִϸ��̼�
	
	Image* _img;		//���ʹ� �̹���
	Image* _shadow;		//�׸��� �̹���
	Image* _backBar;	//ü�¹� �̹���
	Image* _middleBar;
	Image* _frontBar;
	FloatRect _rc;		//���ʹ� ��Ʈ
	FloatRect _pRc;		//�÷��̾� ��Ʈ
	FloatRect _attackRc;//���ݷ�Ʈ

	int _maxHP, _curHP, _saveHP;			//���ʹ� HP
	int _index;			//Ű�ִϿ� ����ϴ� �ε���
	int _attackDelay;	//���� �����̿�
	int _middleBarCut;	//�̵�� ���� �پ���...
	int _rndX;			//astar ���� �� �ذ�
	int _rndY;			//�̰Ͷ���..
	int _hitCount;		//������ ��¦
	int _bossHitCount;
	int _isHitCount;	//isHit�� ī��Ʈ��


	float _x, _y, _z;		//���ʹ� �߽�
	float _width, _height;//ũ��
	float _pX, _pY;		//�÷��̾� �߽�	
	float _angle;		//�� �ޱ�
	float _moveAngle;	//astar�ޱ�
	float _attackAngle;	//������ �޷����� ���� �ޱ� �־��ַ���
	float _scale;		//���ʹ� �׸����� ������ �ַ���
	float _speed;		//���ʹ� �����̴� ���ǵ�
	float _barAlpha;	//�������� ��� ��������


	bool _isAttack;		//�����ϴ���?
	bool _isCol;
	bool _onceAni;		//�ִ� ��ŸƮ �ϴ°� �� ���� ������..
	bool _realDead;		//�ִ� �� �ϱ� ���ʹ� �������� �ϴ°�
	bool _isHit;		//����
	bool _isBossPull;	//���� ������
	bool _isBossPush;	//���� ��
	bool _isRockBottom;
		


public:

	virtual HRESULT init(int index, float x, float y, float width, float height, ENEMYTYPE type);
	virtual void release();
	virtual void update();
	virtual void render();
	void playerCheck(float x, float y, FloatRect rc); //���߿� ���⿡ ��Ʈ �߰���
	virtual void attack() {}	//���ʹ� ���� ���� ��
	virtual void enemyMove() {}	// ������ ���� ��
	virtual void dead() {}		//���ʹ� �״°�
	virtual void set() {}		//��ӹ޾Ƽ� �ʱ�ȭ �� ��
	virtual void enemyWay();	//���� ����
	virtual void move();		//astar
	virtual void hitMove();		//�������̸� �ݴ�� �����̰�
	virtual void directionCheck() {}//�� ���� �����ִ°�
	virtual void enemyHit() {}	//�� ������ �ٲ��ִ°�
	virtual void setShadow() {}	//�� �׸��� ĳ���͸��� ��ġ �ٸ��� ���ַ��� 
	void setBar();				//���ʹ̸��� ü�¹� ��ġ ������
	void ani();					//�̹��� �ִ� �� ������
	void checkBoolCount();		//�Ұ��̶� ī��Ʈ üũ��

	void setGauge(float curHP, float maxHP);	//ü�¹�

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

