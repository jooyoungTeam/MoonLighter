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
	
	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		CAMERAMANAGER->shakeCamera(5, 50);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F12))
	{
		CAMERAMANAGER->fadeInOut(FADETYPE::FADEIN);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F11))
	{
		CAMERAMANAGER->fadeInOut(FADETYPE::FADEOUT);
	}


	cursor();
	_stageManager->update();


	CAMERAMANAGER->cameraUpdate();
}

//�׸��� ����
void playGround::render()
{
	// ����� �ʱ�ȭ
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::White);
	{
		_stageManager->render();


		TIMEMANAGER->render();


		CAMERAMANAGER->fadeRender();
		// ������ ����
		int w = _ptMouse.x + (ImageManager::GetInstance()->FindImage("Ŀ��")->GetFrameSize().x * 0.5f) * 0.5f;
		int h = _ptMouse.y + (ImageManager::GetInstance()->FindImage("Ŀ��")->GetHeight() * 0.5f) * 0.5f;
		ImageManager::GetInstance()->FindImage("Ŀ��")->SetScale(0.5f);
		ImageManager::GetInstance()->FindImage("Ŀ��")->FrameRender(Vector2(w, h), _cursorFrameX, 0);
	}
	// ����ۿ� �׸� ������� ȭ�鿡 �ѷ���.
	D2DRenderer::GetInstance()->EndRender();
}

void playGround::imageLoad()
{
	//===========================================���MAPTOOL���===========================================//
	ImageManager::GetInstance()->AddFrameImage("Ŀ��", L"cursor.png", 6, 1);
	ImageManager::GetInstance()->AddImage("��", L"Object/build_Shop.png");
	ImageManager::GetInstance()->AddFrameImage("mapTiles", L"mapTiles.png", SAMPLETILEX, SAMPLETILEY);
	ImageManager::GetInstance()->AddImage("map1", L"Image/map/map1.png");
	ImageManager::GetInstance()->AddImage("sampleUI", L"Object/sampleUI.png");
	ImageManager::GetInstance()->AddImage("sampleUIOnOff", L"Object/sampleUIOnOff.png");
	ImageManager::GetInstance()->AddImage("objectArchitecture", L"Object/objectArchitecture.png");
	ImageManager::GetInstance()->AddImage("objectDoor", L"Object/objectDoor.png");
	ImageManager::GetInstance()->AddImage("objectHouse", L"Object/objectHouse.png");

	ImageManager::GetInstance()->AddImage("build_Bottom2", L"Object/build_Bottom2.png");
	ImageManager::GetInstance()->AddImage("build_Shop", L"Object/build_Shop.png");
	ImageManager::GetInstance()->AddImage("build_Enchant", L"Object/build_Enchant.png");

	ImageManager::GetInstance()->AddImage("build_Well", L"Object/build_Well.png");
	ImageManager::GetInstance()->AddImage("buildBoard", L"Object/buildBoard.png");
	ImageManager::GetInstance()->AddImage("build_fountain", L"Object/build_fountain.png");
	ImageManager::GetInstance()->AddImage("bench", L"Object/bench.png");

	//===========================================�������ۡ��===========================================//
	ImageManager::GetInstance()->AddImage("slime_red", L"Image/Item/slime_jelly.png");
	ImageManager::GetInstance()->AddImage("slime_blue", L"Image/Item/slime_jelly_blue.png");
	ImageManager::GetInstance()->AddImage("slime_yellow", L"Image/Item/slime_jelly_yellow.png");
	ImageManager::GetInstance()->AddImage("fabric", L"Image/Item/fabric.png");
	ImageManager::GetInstance()->AddImage("vine", L"Image/Item/Vine.png");
	ImageManager::GetInstance()->AddImage("wood", L"Image/Item/Treated_Wood.png");
	ImageManager::GetInstance()->AddImage("golem_pieces", L"Image/Item/golem_pieces.png");
	ImageManager::GetInstance()->AddImage("golem_core", L"Image/Item/Golem_Core.png");
	ImageManager::GetInstance()->AddImage("broken_sword", L"Image/Item/Broken_Sword.png");
	ImageManager::GetInstance()->AddImage("crystal_energy", L"Image/Item/Crystal_Energy.png");
	ImageManager::GetInstance()->AddImage("reinforced_steel", L"Image/Item/Reinforced_Steel_G.png");
	ImageManager::GetInstance()->AddImage("golemKing_Energy", L"Image/Item/Energy_Crystal.png");
	ImageManager::GetInstance()->AddImage("golemKing_record", L"Image/Item/Golem_King_design.png");
	ImageManager::GetInstance()->AddImage("potion_S", L"Image/Item/Potion_S.png");

	//===========================================����κ��丮���===========================================//
	ImageManager::GetInstance()->AddImage("bagMirror", L"image/UI/bagMirror.png");
	ImageManager::GetInstance()->AddFrameImage("mirror_stay", L"image/UI/mirror_stay.png", 11, 1);
	ImageManager::GetInstance()->AddFrameImage("mirror_active", L"image/UI/mirror_active.png", 14, 1);
	ImageManager::GetInstance()->AddImage("inven", L"Image/UI/inventory.png");
	ImageManager::GetInstance()->AddImage("invenSpace", L"image/UI/invenSpace.png");
	ImageManager::GetInstance()->AddImage("select", L"image/UI/invenslot.png");
	ImageManager::GetInstance()->AddImage("selectShowcase", L"image/UI/showcaseSlot.png");
	ImageManager::GetInstance()->AddImage("pendant", L"image/UI/pendant.png");
	ImageManager::GetInstance()->AddImage("empty_weapon", L"image/UI/empty_sword.png");
	ImageManager::GetInstance()->AddImage("empty_helmet", L"image/UI/empty_helmet.png");
	ImageManager::GetInstance()->AddImage("empty_top", L"image/UI/empty_top.png");
	ImageManager::GetInstance()->AddImage("empty_shoes", L"image/UI/empty_shoes.png");
	ImageManager::GetInstance()->AddImage("inven_weapon_1", L"Image/UI/Inven_weapon_1.png");
	ImageManager::GetInstance()->AddImage("inven_weapon_2", L"Image/UI/Inven_weapon_2.png");
	ImageManager::GetInstance()->AddImage("empty_potion", L"Image/UI/empty_potion.png");
	ImageManager::GetInstance()->AddImage("inven_select", L"Image/UI/inven_select.png");
	ImageManager::GetInstance()->AddFrameImage("mirror_ball", L"Image/UI/mirror_empty.png", 10, 1);
	ImageManager::GetInstance()->AddFrameImage("mirror_sale", L"Image/UI/inven_sale.png", 29, 1);
	ImageManager::GetInstance()->AddFrameImage("inven_sale", L"Image/UI/mirror_sale.png", 8, 1);
	ImageManager::GetInstance()->AddImage("showcase", L"Image/UI/showcase.png");

	//===========================================���UI���===========================================//
	ImageManager::GetInstance()->AddImage("UI_base", L"Image/UI/UI_base.png");
	ImageManager::GetInstance()->AddImage("UI_weapon_1", L"Image/UI/UI_weapon_1.png");
	ImageManager::GetInstance()->AddImage("UI_weapon_2", L"Image/UI/UI_weapon_2.png");
	ImageManager::GetInstance()->AddImage("bow", L"Image/UI/Bow.png");
	ImageManager::GetInstance()->AddImage("sword", L"Image/UI/Sword.png");
	ImageManager::GetInstance()->AddImage("UI_pendant", L"image/UI/UI_pendant.png");
	ImageManager::GetInstance()->AddImage("UI_pendant_ring", L"Image/UI/UI_pendant_ring.png");
	ImageManager::GetInstance()->AddImage("UI_front", L"Image/UI/UI_front.png");
	ImageManager::GetInstance()->AddImage("note", L"image/UI/note.png");
	ImageManager::GetInstance()->AddFrameImage("HPbar", L"Image/UI/HPbar.png", 1, 5);
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
