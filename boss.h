#pragma once
#include"enemy.h"
enum BOSS_PATTERN
{
	ATTACK1,
	ATTACK2,
	ATTACK3,
};
struct tagAttack1
{
	FloatRect rc;
	FloatRect attackRc;
	float x, y;
	float speed;
	float width, height;
	float angle;
	bool isBottom;
	bool onceImage;
	int xRandom;
	int yRandom;
	int count;
	int delay;
	int aniDelayCount;
	int index;
	Image* img;
	Image* hole;
};
//struct tagAttackRect
//{
//	FloatRect rc;
//	bool attackDir;
//	float x, y;
//	float speed;
//};
class boss : public enemy	
{
private:
	//vector<tagAttack1> _vAttack1;
	tagAttack1 _attack1;
	tagAttack1 _attack2;
	tagAttack1 _attack3;
//	tagAttackRect _attack2Rc[10];
	Vector2 _leftTop, _leftBottom, _rightTop, _rightBottom;
	BOSS_PATTERN _bossPattern;
	bool _isBossAttack;
	bool _isBossAttackEnd;
	bool _isHandCol;
	int _bossAttackCount;

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
	void attack1_1();
	void attack2_1();
	void attack3_1();
	void attack2Angle();


	tagAttack1* getBAttack2() { return &_attack2; }
	bool getHandCol() { return _isHandCol; }
};

