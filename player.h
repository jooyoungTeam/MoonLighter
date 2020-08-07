#pragma once
#include "gameNode.h"
#include "playerState.h"

class player : public gameNode
{
private:
	FloatRect			_rc;						//플레이어 렉트
	Image*				_playerimg;					//플레이어 이미지
	playerState*		_CurrentState;				//현재 클래스 상태
	animation*			_aniMotion;					//플레이어 애니메이션

	int					_index;						//플레이어 인덱스 0
	float			    _x, _y;

	playerState*	    _idle;

public:

	virtual HRESULT init();
	void render();
	void update();
	void release();

public:
	void animationLoad();

public:
	float getX() { return _x; }
	float getY() { return _y; }

public:
	playerState* getIdle() { return _idle; }

};



