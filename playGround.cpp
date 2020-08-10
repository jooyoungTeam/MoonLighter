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

	ShowCursor(false);

	imageLoad();


	_stageManager = new stageManager;
	_stageManager->init();

	return S_OK;
}

//메모리 해제
void playGround::release()
{
	_stageManager->release();
}

//연산
void playGround::update()
{
	gameNode::update();
	cursor();
	_stageManager->update();
}

//그리기 전용
void playGround::render()
{
	// 백버퍼 초기화
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::White);
	{
		_stageManager->render();


		TIMEMANAGER->render();







		// 마지막 렌더
		ImageManager::GetInstance()->FindImage("커서")->FrameRender(Vector2(_ptMouse.x, _ptMouse.y), _cursorFrameX, 0);
	}
	// 백버퍼에 그린 내용들을 화면에 뿌려라.
	D2DRenderer::GetInstance()->EndRender();
}

void playGround::imageLoad()
{
	ImageManager::GetInstance()->AddFrameImage("커서", L"cursor.png", 6, 1);
}

void playGround::cursor()
{
	_count++;
	if (_count % 10 == 0)
	{
		_cursorFrameX++;
		_count = 0;
		if (_cursorFrameX > 5)
		{
			_cursorFrameX = 0;
		}
	}
}
