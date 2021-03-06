#include "stdafx.h"
#include "title.h"

HRESULT title::init()
{
	_titleFront = ImageManager::GetInstance()->AddFrameImage("titleFront", L"image/UI/titleFront.png", 16, 1);
	_titleBack = ImageManager::GetInstance()->AddFrameImage("titleBack", L"image/UI/titleBack.png", 16, 1);
	_logo = ImageManager::GetInstance()->AddImage("logo", L"image/UI/logo.png");
	_menuBox = ImageManager::GetInstance()->AddImage("menuBox", L"image/UI/menuBox.png");

	_selectImg = ImageManager::GetInstance()->AddImage("bagMirror", L"image/UI/bagMirror.png");
	ImageManager::GetInstance()->AddFrameImage("mirror_stay", L"image/UI/mirror_stay.png", 11, 1);

	_menu[0].name = L"START";
	_menu[1].name = L"MAPTOOL";
	_menu[2].name = L"EXIT";

	for (int i = 0; i < MENUNUM; i++)
	{
		int n = _menu[i].name.length();
		_menu[i].rc = RectMakePivot(Vector2(WINSIZEX / 2, (WINSIZEY / 2 + 50)+ i * 100), Vector2(n * 20, 50), Pivot::Center);
	}

	_select = _count = _frameCount = 0;
	_selectX = _frameX = 0;
	_menuSelect = SELECT::STOP;

	return S_OK;
}

void title::update()
{
	draw();

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		SOUNDMANAGER->play("click");
		_select++;
		if (_select > 2) _select = 0;
		_selectImg = ImageManager::GetInstance()->FindImage("bagMirror");
		_menuSelect = SELECT::MOVE;
		_count = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		SOUNDMANAGER->play("click");
		_select--;
		if (_select < 0) _select = 2;
		_selectImg = ImageManager::GetInstance()->FindImage("bagMirror");
		_menuSelect = SELECT::MOVE;
		_count = 0;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		SOUNDMANAGER->play("click");
		_menuSelect = SELECT::STOP;
	}

	if (_menuSelect == SELECT::STOP)
	{
		_count++;
		_selectX = 0;

		if (_count > 20)
		{
			_menuSelect = SELECT::STAY;
			_selectImg = ImageManager::GetInstance()->FindImage("mirror_stay");
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->play("gameStart");
		_count = 0;

		if (_select == 0) SCENEMANAGER->changeScene("����");
		if (_select == 1) SCENEMANAGER->changeScene("Ÿ�Ͼ�");
		if (_select == 2) SCENEMANAGER->changeScene("������");
	}	
}

void title::render()
{
	_titleBack->SetSize(Vector2(WINSIZEX, WINSIZEY));
	_logo->SetSize(Vector2(600, 300));
	_menuBox->SetSize(Vector2(800, 500));
	_titleFront->SetSize(Vector2(WINSIZEX, WINSIZEY));

	_titleBack->FrameRender(Vector2(WINSIZEX / 2, WINSIZEY / 2), _frameX, 0);
	_logo->Render(Vector2(WINSIZEX / 2 - 300, WINSIZEY / 2 - 400));
	_menuBox->Render(Vector2(WINSIZEX / 2 - 400, WINSIZEY / 2 - 150));

	for (int i = 0; i < MENUNUM; i++)
	{
		//D2DRenderer::GetInstance()->DrawRectangle(_menu[i].rc, D2DRenderer::DefaultBrush::White, 1.f);
	}	

	D2DRenderer::GetInstance()->RenderText(_menu[0].rc.GetCenter().x - _menu[0].name.length() * 10 + 10, _menu[0].rc.GetCenter().y - 20, _menu[0].name, 30, D2DRenderer::DefaultBrush::White);
	D2DRenderer::GetInstance()->RenderText(_menu[1].rc.GetCenter().x - _menu[1].name.length() * 10, _menu[1].rc.GetCenter().y - 20, _menu[1].name, 30, D2DRenderer::DefaultBrush::White);
	D2DRenderer::GetInstance()->RenderText(_menu[2].rc.GetCenter().x - _menu[2].name.length() * 10 + 10, _menu[2].rc.GetCenter().y - 20, _menu[2].name, 30, D2DRenderer::DefaultBrush::White);

	if (_menuSelect == SELECT::MOVE || _menuSelect == SELECT::STOP) _selectImg->Render(Vector2(_menu[_select].rc.GetCenter().x - 150, _menu[_select].rc.GetCenter().y - 100));
	if (_menuSelect == SELECT::STAY && _count > 20) _selectImg->FrameRender(Vector2(_menu[_select].rc.GetCenter().x - 25, _menu[_select].rc.GetCenter().y + 35), _selectX, 0);

	_titleFront->FrameRender(Vector2(WINSIZEX / 2, WINSIZEY / 2), _frameX, 0);
}

void title::release()
{
}

void title::draw()
{
	_frameCount++;

	if (_frameCount % 5 == 0)
	{
		_frameX++;

		if (_frameX > 15)
		{
			_frameX = 0;
		}
	}

	if (_frameCount % 7 == 0)
	{
		_selectX++;

		if (_selectX > 10)
		{
			_selectX = 3;
		}
		_frameCount = 0;
	}
}
