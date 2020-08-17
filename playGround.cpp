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

//그리기 전용
void playGround::render()
{
	// 백버퍼 초기화
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::White);
	{
		_stageManager->render();


		TIMEMANAGER->render();


		CAMERAMANAGER->fadeRender();
		// 마지막 렌더
		int w = _ptMouse.x + (ImageManager::GetInstance()->FindImage("커서")->GetFrameSize().x * 0.5f) * 0.5f;
		int h = _ptMouse.y + (ImageManager::GetInstance()->FindImage("커서")->GetHeight() * 0.5f) * 0.5f;
		ImageManager::GetInstance()->FindImage("커서")->SetScale(0.5f);
		ImageManager::GetInstance()->FindImage("커서")->FrameRender(Vector2(w, h), _cursorFrameX, 0);
	}
	// 백버퍼에 그린 내용들을 화면에 뿌려라.
	D2DRenderer::GetInstance()->EndRender();
}

void playGround::imageLoad()
{
	//===========================================↓↓MAPTOOL↓↓===========================================//
	ImageManager::GetInstance()->AddFrameImage("커서", L"cursor.png", 6, 1);
	ImageManager::GetInstance()->AddImage("샵", L"Object/build_Shop.png");
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
	ImageManager::GetInstance()->AddImage("objectPlant", L"Object/objectPlant.png");

	ImageManager::GetInstance()->AddImage("objectNPC", L"Object/objectNPC.png");
	ImageManager::GetInstance()->AddImage("object_door1", L"Object/object_door1.png");
	ImageManager::GetInstance()->AddImage("object_door2", L"Object/object_door2.png");
	ImageManager::GetInstance()->AddImage("object_door3", L"Object/object_door3.png");
	ImageManager::GetInstance()->AddImage("object_door4", L"Object/object_door4.png");
	ImageManager::GetInstance()->AddImage("objectSpa", L"Object/objectSpa.png");
	ImageManager::GetInstance()->AddImage("plant_flower", L"Object/plant_flower.png");
	ImageManager::GetInstance()->AddImage("spa", L"Object/spa.png");

	ImageManager::GetInstance()->AddFrameImage("plant_tree1", L"Object/plant_tree1.png", 35, 1);
	ImageManager::GetInstance()->AddFrameImage("plant_tree2", L"Object/plant_tree2.png", 35, 1);
	ImageManager::GetInstance()->AddFrameImage("plant_fountain1", L"Object/plant_fountain1.png", 9, 1);
	ImageManager::GetInstance()->AddFrameImage("Object_build_Bottom1", L"Object/Object_build_Bottom1.png", 53, 1);

	ImageManager::GetInstance()->AddFrameImage("npc_1", L"Object/npc_1.png", 17, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_2", L"Object/npc_2.png", 54, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_3", L"Object/npc_3.png", 24, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_4", L"Object/npc_4.png", 49, 1);

	ImageManager::GetInstance()->AddImage("objectDungeon1", L"Object/objectDungeon1.png");
	ImageManager::GetInstance()->AddImage("objectDungeon2", L"Object/objectDungeon2.png");
	ImageManager::GetInstance()->AddImage("object_skull1", L"Object/skull1.png");
	ImageManager::GetInstance()->AddImage("object_skull2", L"Object/skull2.png");
	ImageManager::GetInstance()->AddImage("object_skull3", L"Object/skull3.png");
	ImageManager::GetInstance()->AddImage("object_pot", L"Object/pot.png");
	ImageManager::GetInstance()->AddImage("object_pot_slime", L"Object/pot_slime.png");
	ImageManager::GetInstance()->AddImage("object_pillar", L"Object/pillar.png");
	ImageManager::GetInstance()->AddImage("object_smallRock", L"Object/smallRock.png");
	ImageManager::GetInstance()->AddImage("object_smallRock_slime", L"Object/smallRock_slime.png");



	//===========================================↓↓아이템↓↓===========================================//
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

	//===========================================↓↓인벤토리↓↓===========================================//
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

	//===========================================↓↓UI↓↓===========================================//
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
