#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);
	_tile = new tile;
	_tile->init();

	return S_OK;
}

//메모리 해제
void playGround::release()
{
}

//연산
void playGround::update()
{
	gameNode::update();

	_tile->update();
}

//그리기 전용
void playGround::render()
{
	// 백버퍼 초기화
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::White);
	{
		_tile->render();

	}
	// 백버퍼에 그린 내용들을 화면에 뿌려라.
	D2DRenderer::GetInstance()->EndRender();
}
