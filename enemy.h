#pragma once
#include "gameNode.h"
#include "enemyState.h"
#include "item.h"
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
	item*  _item;
	ENEMYTYPE _type;
	GOLEMDIR _golemDir;
	POTDIR _potDir;
	BOSS_ANI _bossAni;
	BOSS_PATTERN _bossPattern;

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
	int _attackDelay;	//���� �����̿�
	int _middleBarCut;	//�̵�� ���� �پ���...
	int _rndX;			//astar ���� �� �ذ�
	int _rndY;			//�̰Ͷ���..
	int _hitCount;		//������ ��¦
	int _bossHitCount;
	int _isHitCount;	//isHit�� ī��Ʈ��
	int _startDelay;


	float _x, _y, _z;		//���ʹ� �߽�
	float _width, _height;//ũ��
	float _pX, _pY;		//�÷��̾� �߽�	
	float _angle;		//�� �ޱ�
	float _moveAngle;	//astar�ޱ�
	float _attackAngle;	//������ �޷����� ���� �ޱ� �־��ַ���
	float _scale;		//���ʹ� �׸����� ������ �ַ���
	float _speed;		//���ʹ� �����̴� ���ǵ�
	float _barAlpha;	//�������� ��� ��������
	float _bowTimer;


	bool _isAttack;		//�����ϴ���?
	bool _isCol;		//���� ������ �����̶� ���.
	bool _isPlayerHit;
	bool _onceAni;		//�ִ� ��ŸƮ �ϴ°� �� ���� ������..
	bool _realDead;		//�ִ� �� �ϱ� ���ʹ� �������� �ϴ°�
	bool _isHit;		//����
	bool _isBossPull;	//���� ������
	bool _isBossPush;	//���� ��
	bool _isRockBottom;	//���� �� �ٴڿ� ��Ҵ���
	bool _patternCheck;	//���� ���� �ٲٱ� ��
	bool _playerStop;	//�÷��̾� ���߱��
	bool _isPowerShot;	//Ȱ ������ �ѹ��°�
		


public:

	virtual HRESULT init(float x, float y, float width, float height, ENEMYTYPE type, vector<POINT> unMoveTile);
	virtual void release();
	virtual void update();
	virtual void render();
	void playerCheck(float x, float y, FloatRect rc, bool playerStop); //���߿� ���⿡ ��Ʈ �߰���
	virtual void attack() {}	//���ʹ� ���� ���� ��
	virtual void enemyMove() {}	// ������ ���� ��
	virtual void dead();		//���ʹ� �״°�
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
	void setBossPattern(BOSS_PATTERN pattern) { _bossPattern = pattern; }

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
	void setPatternCheck(bool pattern) { _patternCheck = pattern; }
	void setIsPlayerHit(bool hit) { _isPlayerHit = hit; }
	void setIsPowerShot(bool shot) { _isPowerShot = shot; }

	void setEnemyAttack(int hp = 30)
	{
		if (_curHP <= 0)
		{
			return;
		}
		if (_state != _dead && _state != _hit)
		{
			if (_type != ENEMY_BOSS)
			{
				_isHit = true;
				_barAlpha = 1.0f;
			}

			_saveHP = _bar.width;
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
			_curHP -= hp;
		}
		if (_curHP <= 0)
		{

			if (_state != _dead)
			{
				_bossAni = ONE;
				_onceAni = true;
				_state = _dead;
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

	int getAttackDelay() { return _attackDelay; }
	int getCurHP() { return _curHP; }
	int getSaveHP() { return _saveHP; }

	bool getIsAttack() { return _isAttack; }
	bool getIsCol() { return _isCol; }
	bool getRealDead() { return _realDead; }
	bool getIsHit() { return _isHit; }
	bool getIsPull() { return _isBossPull; }
	bool getIsPush() { return _isBossPush; }
	bool getIsRockBottom() { return _isRockBottom; }
	bool getOnceAni() { return _onceAni; }
	bool getIsPlayerHit() { return _isPlayerHit; }
	bool getPlayerStop() { return _playerStop; }
	bool getIsPowerShot() { return _isPowerShot; }

	tagBar getBar() { return _bar; }
	FloatRect getEnemyAttackRect() { return _attackRc; }
	FloatRect getEnemyRect() { return _rc; }
	FloatRect getPlayerRect() { return _pRc; }
	animation* getAni() { return _motion; }

	GOLEMDIR getGolDriection() { return _golemDir; }
	POTDIR getPotDirection() { return _potDir; }
	ENEMYTYPE getEnemyType() { return _type; }
	BOSS_PATTERN getBossPattern() { return _bossPattern; }

	enemyState* getState() { return _state; }
	enemyState* getIdle() { return _idle; }			
	enemyState* getMove() { return _move; }
	enemyState* getAttack() { return _attack; }
	enemyState* getHit() { return _hit; }
	enemyState* getDead() { return _dead; }


};

