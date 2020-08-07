#pragma once
#include "gameNode.h"
#include "playerState.h"

class player : public gameNode
{
private:
	FloatRect			_rc;						//�÷��̾� ��Ʈ
	Image*				_playerimg;					//�÷��̾� �̹���
	playerState*		_CurrentState;				//���� Ŭ���� ����
	animation*			_aniMotion;					//�÷��̾� �ִϸ��̼�

	int					_index;						//�÷��̾� �ε��� 0
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



