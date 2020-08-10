#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	gameNode::init(true);

	ShowCursor(false);

	imageLoad();


	_stageManager = new stageManager;
	_stageManager->init();

	return S_OK;
}

//�޸� ����
void playGround::release()
{
	_stageManager->release();
}

//����
void playGround::update()
{
	gameNode::update();
	cursor();
	_stageManager->update();
}

//�׸��� ����
void playGround::render()
{
	// ����� �ʱ�ȭ
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::White);
	{
		_stageManager->render();


		TIMEMANAGER->render();







		// ������ ����
		ImageManager::GetInstance()->FindImage("Ŀ��")->FrameRender(Vector2(_ptMouse.x, _ptMouse.y), _cursorFrameX, 0);
	}
	// ����ۿ� �׸� ������� ȭ�鿡 �ѷ���.
	D2DRenderer::GetInstance()->EndRender();
}

void playGround::imageLoad()
{
	ImageManager::GetInstance()->AddFrameImage("Ŀ��", L"cursor.png", 6, 1);
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
