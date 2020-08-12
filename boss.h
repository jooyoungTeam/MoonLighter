#pragma once
#include"enemy.h"
enum BOSS_PATTERN
{
	ATTACK1,
	ATTACK2,
};
struct tagAttack1
{
	FloatRect rc;
	FloatRect attackRc;
	float x, y;
	float speed;
	float width, height;
	float _angle;
	bool isBottom;
	bool onceImage;
	int xRandom;
	int yRandom;
	int count;
	int delay;
	int aniDelayCount;
	int index;
	Image* img;
};
class boss : public enemy	
{
private:
	//vector<tagAttack1> _vAttack1;

	tagAttack1 _attack1;
	tagAttack1 _attack2;
	BOSS_PATTERN _bossPattern;
	bool _isBossAttack;
	bool _isBossAttackEnd;
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
	void attack1_1();
	void attack2_1();
};

