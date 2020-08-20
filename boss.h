#pragma once
#include"enemy.h"

struct tagAttack1
{
	FloatRect rc;
	FloatRect attackRc;
	float x, y;
	float speed;
	float width, height;
	float angle;
	bool isAttack;
	int xRandom;
	int yRandom;
	int count;
	int delay;
	int aniDelayCount;
	int index;
	Image* img;
	Image* hole;
};
struct tagAttackRect
{
	FloatRect rc;
	FloatRect attackRc;
	float x, y;
	float mX, mY;
	float width;
	float speed;
	bool rackFall;
	float alpha;
	float rockAlpha;
	float scale;
	int attackCount;
	int rackCount;
	int random;
};
class boss : public enemy	
{
private:
	//vector<tagAttack1> _vAttack1;
	tagAttack1 _attack1;
	tagAttack1 _attack2;
	tagAttack1 _attack3;
	tagAttackRect _attack3Rc[17];
	tagAttackRect _attack3Rc2[15];
	Vector2 _leftTop, _leftBottom, _rightTop, _rightBottom;

	player* _player;
	Image* _effectImage;
	FloatRect _attackRc;
	float _handAngle1;
	float _handAngle2;
	float _eX, _eY;
	bool _isHandCol;
	bool _playerCol;
	bool _playerStop;
	bool _onceSound;
	int _cameraShake;
	int _bossAttackCount;
	int _patternRandom;
	int _saveRandom;
	int _exCount;
	int _attackTimer;
	int _hitTimer;
	int _index;
	int _aniCount;


public:
	boss() {}
	~boss() {}

	virtual void set();
	virtual void render();
	virtual void attack();
	virtual void dead();
	virtual void enemyHit();
	void attack1();	
	void attack2();
	void attack3();
	void attack4();
	void attack5();
	void attack1_1();
	void attack2_1();
	void attack3_1();
	void attack3_2();
	void attack3_3();
	void attack2Angle();
	void setRock();
	bool playerCol();
	bool playerStop(RECT& rc);
	void effect();


	tagAttack1* getBAttack2() { return &_attack2; }
	tagAttack1* getBAttack3() { return &_attack3; }
	tagAttackRect* getBAttack3Rc() { return _attack3Rc; }
	bool getBossPlayerCol() { return _playerCol; }
	bool getBPlayerStop() { return _playerStop; }
};

