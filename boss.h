#pragma once
#include"enemy.h"
enum BOSS_PATTERN
{
	ATTACK1,
	ATTACK2,
	ATTACK3,
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
	float rackAlpha;
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
	tagAttackRect _attack3Rc[13];
	tagAttackRect _attack3Rc2[13];
	Vector2 _leftTop, _leftBottom, _rightTop, _rightBottom;
	BOSS_PATTERN _bossPattern;
	BOSS_ANI _bossAni;

	float _handAngle1;
	float _handAngle2;
	bool _isHandCol;
	bool _patternCheck;
	bool _playerCol;
	int _cameraShake;
	int _bossAttackCount;
	int _patternRandom;
	int _saveRandom;

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
	void attack1_1();
	void attack2_1();
	void attack3_1();
	void attack3_2();
	void attack2Angle();
	void setRock();
	void playerCol();


	tagAttack1* getBAttack2() { return &_attack2; }
	bool getHandCol() { return _isHandCol; }
};

