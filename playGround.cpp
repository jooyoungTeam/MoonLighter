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
		int w = _ptMouse.x + (ImageManager::GetInstance()->FindImage("커서")->GetFrameSize().x) * 0.5f;
		int h = _ptMouse.y + (ImageManager::GetInstance()->FindImage("커서")->GetHeight()) * 0.5f;
		ImageManager::GetInstance()->FindImage("커서")->SetScale(0.7f);
		ImageManager::GetInstance()->FindImage("커서")->FrameRender(Vector2(w - 11, h - 14), _cursorFrameX, 0);
	}
	// 백버퍼에 그린 내용들을 화면에 뿌려라.
	D2DRenderer::GetInstance()->EndRender();
}

void playGround::imageLoad()
{
	ImageManager::GetInstance()->AddFrameImage("커서", L"cursor.png", 6, 1);
	ImageManager::GetInstance()->AddImage("집1", L"Object/build_Bottom1.png");
	ImageManager::GetInstance()->AddImage("집2", L"Object/build_Bottom2.png");
	ImageManager::GetInstance()->AddImage("샵", L"Object/build_Shop.png");
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
