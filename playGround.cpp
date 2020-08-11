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
		int w = _ptMouse.x + (ImageManager::GetInstance()->FindImage("Ŀ��")->GetFrameSize().x) * 0.5f;
		int h = _ptMouse.y + (ImageManager::GetInstance()->FindImage("Ŀ��")->GetHeight()) * 0.5f;
		ImageManager::GetInstance()->FindImage("Ŀ��")->SetScale(0.7f);
		ImageManager::GetInstance()->FindImage("Ŀ��")->FrameRender(Vector2(w - 11, h - 14), _cursorFrameX, 0);
	}
	// ����ۿ� �׸� ������� ȭ�鿡 �ѷ���.
	D2DRenderer::GetInstance()->EndRender();
}

void playGround::imageLoad()
{
	ImageManager::GetInstance()->AddFrameImage("Ŀ��", L"cursor.png", 6, 1);
	ImageManager::GetInstance()->AddImage("��1", L"Object/build_Bottom1.png");
	ImageManager::GetInstance()->AddImage("��2", L"Object/build_Bottom2.png");
	ImageManager::GetInstance()->AddImage("��", L"Object/build_Shop.png");
	ImageManager::GetInstance()->AddFrameImage("mapTiles", L"mapTiles.png", SAMPLETILEX, SAMPLETILEY);
	ImageManager::GetInstance()->AddImage("map1", L"Image/map/map1.png");
	ImageManager::GetInstance()->AddImage("sampleUI", L"Object/sampleUI.png");
	ImageManager::GetInstance()->AddImage("sampleUIOnOff", L"Object/sampleUIOnOff.png");
	ImageManager::GetInstance()->AddImage("objectArchitecture", L"Object/objectArchitecture.png");
	ImageManager::GetInstance()->AddImage("objectDoor", L"Object/objectDoor.png");
	ImageManager::GetInstance()->AddImage("objectHouse", L"Object/objectHouse.png");

	ImageManager::GetInstance()->AddImage("build_Bottom1", L"Object/build_Bottom1.png");
	ImageManager::GetInstance()->AddImage("build_Bottom2", L"Object/build_Bottom2.png");
	ImageManager::GetInstance()->AddImage("build_Shop", L"Object/build_Shop.png");
	ImageManager::GetInstance()->AddImage("build_Enchant", L"Object/build_Enchant.png");

	ImageManager::GetInstance()->AddImage("build_Well", L"Object/build_Well.png");
	ImageManager::GetInstance()->AddImage("buildBoard", L"Object/buildBoard.png");
	ImageManager::GetInstance()->AddImage("build_fountain", L"Object/build_fountain.png");
	ImageManager::GetInstance()->AddImage("bench", L"Object/bench.png");

	
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
