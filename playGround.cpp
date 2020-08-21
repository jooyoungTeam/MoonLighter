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
	soundLoad();
	imageLoad();
	SOUNDMANAGER->play("Moon", 0.1f);

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


	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		SOUNDMANAGER->play("bed", 1.0f);
	}

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
	ImageManager::GetInstance()->AddFrameImage("object_door1", L"Object/object_door1.png", 5, 1);
	ImageManager::GetInstance()->AddFrameImage("object_door2", L"Object/object_door2.png", 5, 1);
	ImageManager::GetInstance()->AddFrameImage("object_door3", L"Object/object_door3.png", 5, 1);
	ImageManager::GetInstance()->AddFrameImage("object_door4", L"Object/object_door4.png", 5, 1);
	ImageManager::GetInstance()->AddImage("objectSpa", L"Object/objectSpa.png");
	ImageManager::GetInstance()->AddImage("plant_flower", L"Object/plant_flower.png");
	ImageManager::GetInstance()->AddImage("spa", L"Object/spa.png");

	ImageManager::GetInstance()->AddFrameImage("plant_tree1", L"Object/plant_tree1.png", 35, 1);
	ImageManager::GetInstance()->AddFrameImage("plant_tree2", L"Object/plant_tree2.png", 35, 1);
	ImageManager::GetInstance()->AddFrameImage("plant_fountain1", L"Object/plant_fountain1.png", 9, 1);
	ImageManager::GetInstance()->AddFrameImage("Object_build_Bottom1", L"Object/Object_build_Bottom1.png", 53, 1);

	ImageManager::GetInstance()->AddFrameImage("npc_1", L"Object/npc_1.png", 17, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_2", L"Object/npc_2.png", 54, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_3", L"Object/npc_3.png", 26, 1);
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


	ImageManager::GetInstance()->AddImage("objectPlant", L"Object/objectPlant.png");

	ImageManager::GetInstance()->AddImage("objectNPC", L"Object/objectNPC.png");
	ImageManager::GetInstance()->AddImage("object_door1", L"Object/object_door1.png");
	ImageManager::GetInstance()->AddImage("object_door2", L"Object/object_door2.png");
	ImageManager::GetInstance()->AddImage("object_door3", L"Object/object_door3.png");
	ImageManager::GetInstance()->AddImage("object_door4", L"Object/object_door4.png");
	ImageManager::GetInstance()->AddImage("objectSpa", L"Object/objectSpa.png");
	ImageManager::GetInstance()->AddImage("plant_flower", L"Object/plant_flower.png");
	ImageManager::GetInstance()->AddImage("spa", L"Object/spa.png");
	ImageManager::GetInstance()->AddImage("object_rock1", L"Object/objectRock1.png");
	ImageManager::GetInstance()->AddImage("object_rock2", L"Object/objectRock2.png");
	ImageManager::GetInstance()->AddImage("object_tile1", L"Object/object_Tile1.png");
	ImageManager::GetInstance()->AddImage("object_tile2", L"Object/object_Tile2.png");
	ImageManager::GetInstance()->AddImage("object_tile3", L"Object/object_Tile3.png");



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
	ImageManager::GetInstance()->AddImage("objectTile1", L"Object/objectTile1.png");
	ImageManager::GetInstance()->AddImage("objectTile2", L"Object/objectTile2.png");
	ImageManager::GetInstance()->AddImage("objectTile3", L"Object/objectTile3.png");
	ImageManager::GetInstance()->AddImage("objectTile4", L"Object/objectTile4.png");
	ImageManager::GetInstance()->AddImage("objectTile5", L"Object/objectTile5.png");
	ImageManager::GetInstance()->AddImage("objectTile6", L"Object/objectTile6.png");
	ImageManager::GetInstance()->AddImage("objectTile7", L"Object/objectTile7.png");
	ImageManager::GetInstance()->AddImage("objectTile8", L"Object/objectTile8.png");
	ImageManager::GetInstance()->AddImage("objectTile9", L"Object/objectTile9.png");
	ImageManager::GetInstance()->AddImage("objectTile10", L"Object/objectTile10.png");
	ImageManager::GetInstance()->AddImage("objectTile11", L"Object/objectTile11.png");
	ImageManager::GetInstance()->AddImage("objectTile12", L"Object/objectTile12.png");
	ImageManager::GetInstance()->AddImage("rock1", L"Object/rock1.png");
	ImageManager::GetInstance()->AddImage("rock2", L"Object/rock2.png");
	ImageManager::GetInstance()->AddImage("rock3", L"Object/rock3.png");
	ImageManager::GetInstance()->AddImage("rock4", L"Object/rock4.png");
	ImageManager::GetInstance()->AddImage("rock5", L"Object/rock5.png");
	ImageManager::GetInstance()->AddImage("root1", L"Object/root1.png");
	ImageManager::GetInstance()->AddImage("root2", L"Object/root2.png");



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
	ImageManager::GetInstance()->AddImage("potion_M", L"Image/Item/Potion_M.png");
	ImageManager::GetInstance()->AddImage("potion_B", L"Image/Item/Potion_B.png");
	ImageManager::GetInstance()->AddImage("potion_L", L"Image/Item/Potion_L.png");

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
	ImageManager::GetInstance()->AddImage("item_tag", L"Image/UI/item_name.png");

	//===========================================↓↓UI↓↓===========================================//
	ImageManager::GetInstance()->AddImage("UI_base", L"Image/UI/UI_base.png");
	ImageManager::GetInstance()->AddImage("UI_weapon_1", L"Image/UI/UI_weapon_1.png");
	ImageManager::GetInstance()->AddImage("UI_weapon_2", L"Image/UI/UI_weapon_2.png");
	ImageManager::GetInstance()->AddImage("bow", L"Image/UI/Bow.png");
	ImageManager::GetInstance()->AddImage("sword", L"Image/UI/Sword.png");
	ImageManager::GetInstance()->AddImage("inven_bow", L"Image/UI/inven_Bow.png");
	ImageManager::GetInstance()->AddImage("inven_sword", L"Image/UI/inven_Sword.png");
	ImageManager::GetInstance()->AddImage("UI_pendant", L"image/UI/UI_pendant.png");
	ImageManager::GetInstance()->AddImage("UI_pendant_ring", L"Image/UI/UI_pendant_ring.png");
	ImageManager::GetInstance()->AddImage("UI_front", L"Image/UI/UI_front.png");
	ImageManager::GetInstance()->AddImage("note", L"image/UI/note.png");
	ImageManager::GetInstance()->AddFrameImage("HPbar", L"Image/UI/HPbar.png", 1, 5);
	ImageManager::GetInstance()->AddImage("boss_bar", L"Image/UI/Boss_bar.png");
	ImageManager::GetInstance()->AddFrameImage("boss_HP", L"Image/UI/Boss_HP.png", 1, 5);
	ImageManager::GetInstance()->AddFrameImage("boss_scroll", L"Image/UI/Boss_room.png", 1, 9);
	ImageManager::GetInstance()->AddFrameImage("moneyBag", L"Image/UI/money_bag.png", 1, 6);
	ImageManager::GetInstance()->AddImage("price_cursor", L"Image/UI/select_price.png");
	ImageManager::GetInstance()->AddImage("hit_screen", L"Image/UI/player_hit_screen.png");
	ImageManager::GetInstance()->AddImage("UI_gold", L"Image/UI/UI_gold.png");
	ImageManager::GetInstance()->AddImage("J", L"Image/UI/J_key.png");

	//=======================================에너미==============================
	//레드 슬라임
	ImageManager::GetInstance()->AddFrameImage("redSlime", L"image/enemy/slimeIlde.png", 10, 1);
	ImageManager::GetInstance()->AddFrameImage("redSlimeJump", L"image/enemy/slimeJump.png", 12, 1);
	ImageManager::GetInstance()->AddFrameImage("redSlimeDead", L"image/enemy/slimeDead.png", 11, 1);
	ImageManager::GetInstance()->AddFrameImage("slimeAttack", L"image/enemy/slimeAttack.png", 8, 1);

	//블루 슬라임
	ImageManager::GetInstance()->AddFrameImage("blueSlime", L"image/enemy/blueSlime.png", 8, 1);
	ImageManager::GetInstance()->AddFrameImage("blueSlimeDead", L"image/enemy/blueSlimeDead.png", 11, 1);

	//옐로 슬라임
	ImageManager::GetInstance()->AddFrameImage("yellowSlime", L"image/enemy/yellowSlime.png", 8, 1);
	ImageManager::GetInstance()->AddFrameImage("yellowSlimeDead", L"image/enemy/yellowSlimeDead.png", 11, 1);
	ImageManager::GetInstance()->AddFrameImage("yellowSlimePang", L"image/enemy/yellowSlime_pang.png", 7, 1);

	//팟
	ImageManager::GetInstance()->AddFrameImage("bulletCollision", L"image/enemy/bullet_collision.png", 5, 1);
	ImageManager::GetInstance()->AddFrameImage("bullet", L"image/enemy/enemy_bullet.png", 6, 1);
	ImageManager::GetInstance()->AddFrameImage("pot", L"image/enemy/pot.png", 11, 4);
	ImageManager::GetInstance()->AddFrameImage("potDead", L"image/enemy/potDead.png", 18, 1);
	EFFECTMANAGER->addEffect("bulletCollision", "bulletCollision", 90, 18, 18, 18, 1.0f, 0.2f, 10.0f, 1.5f);

	//골렘
	ImageManager::GetInstance()->AddFrameImage("golemAttack", L"image/enemy/GolemAttack.png", 13, 4);
	ImageManager::GetInstance()->AddFrameImage("golem", L"image/enemy/GolemMove.png", 8, 4);
	ImageManager::GetInstance()->AddFrameImage("golemAttackRed", L"image/enemy/GolemAttack_Red.png", 13, 4);
	ImageManager::GetInstance()->AddFrameImage("golemAttackWhite", L"image/enemy/GolemAttack_White.png", 13, 4);
	ImageManager::GetInstance()->AddFrameImage("golemRed", L"image/enemy/GolemMove_Red.png", 8, 4);
	ImageManager::GetInstance()->AddFrameImage("golemWhite", L"image/enemy/GolemMove_White.png", 8, 4);


	//보스
	ImageManager::GetInstance()->AddFrameImage("BossUp", L"image/enemy/BossUp.png", 32, 1);
	ImageManager::GetInstance()->AddFrameImage("bossHit", L"image/enemy/dead1.png", 41, 1);
	ImageManager::GetInstance()->AddFrameImage("bossDead", L"image/enemy/dead2.png", 41, 1);
	ImageManager::GetInstance()->AddFrameImage("bossHandCome", L"image/enemy/Hand_Shoot_Last.png", 11, 1);
	ImageManager::GetInstance()->AddFrameImage("bossAttack", L"image/enemy/attack.png", 7, 1);
	ImageManager::GetInstance()->AddFrameImage("boss", L"image/enemy/idleBoss.png", 2, 1);
	ImageManager::GetInstance()->AddFrameImage("bossAttackIdle", L"image/enemy/attackIdle.png", 2, 1);
	ImageManager::GetInstance()->AddFrameImage("bossHand", L"image/enemy/hand.png", 19, 1);
	ImageManager::GetInstance()->AddFrameImage("bossHandFly", L"image/enemy/FistShoot.png", 22, 3);
	ImageManager::GetInstance()->AddImage("Boss_Rock0", L"image/enemy/Boss_Rock0.png");
	ImageManager::GetInstance()->AddImage("Boss_Rock1", L"image/enemy/Boss_Rock1.png");
	ImageManager::GetInstance()->AddImage("Boss_Rock2", L"image/enemy/Boss_Rock2.png");
	ImageManager::GetInstance()->AddImage("Boss_Rock3", L"image/enemy/Boss_Rock3.png");
	ImageManager::GetInstance()->AddFrameImage("bossLong", L"image/enemy/long.png", 6, 1);


	ImageManager::GetInstance()->AddImage("shadow", L"image/enemy/Shadow.png");
	ImageManager::GetInstance()->AddFrameImage("bossPullEffect", L"image/enemy/bossPullEffect.png", 11, 1);
	ImageManager::GetInstance()->AddImage("bossBullet", L"image/enemy/bossBullet.png");
	ImageManager::GetInstance()->AddFrameImage("bossTornadoEffect", L"image/enemy/bossTornadoEffect.png", 16, 1);
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

//사운드 집합
void playGround::soundLoad()
{
	//플레이어
	SOUNDMANAGER->addSound("bed", "sound/playerSound/침대.wav", false, false);
	SOUNDMANAGER->addSound("Sword", "sound/playerSound/Sword.wav", false, false);
	SOUNDMANAGER->addSound("bow", "sound/playerSound/bow.wav", false, false);
	SOUNDMANAGER->addSound("bow_Attack", "sound/playerSound/bow_Attack.wav", false, false);
	SOUNDMANAGER->addSound("bow_Charge", "sound/playerSound/bow_Charge.wav", false, false);
	SOUNDMANAGER->addSound("healing", "sound/playerSound/회복_샘.wav", false, false);
	SOUNDMANAGER->addSound("potion", "sound/playerSound/potion.wav", false, false);
	SOUNDMANAGER->addSound("Moon", "sound/MoonLighter_Full.mp3", true, false);
	SOUNDMANAGER->addSound("roll", "sound/playerSound/roll.wav", false, false);
	SOUNDMANAGER->addSound("walk", "sound/playerSound/walk.wav", false, false);
	SOUNDMANAGER->addSound("WeaponChange", "sound/playerSound/WeaponChange.wav", false, false);


	//____________________________________________
	//팟
	SOUNDMANAGER->addSound("총알쏘기", "sound/enemySound/에너미/폿/총알쏘기.wav", false, false);
	SOUNDMANAGER->addSound("총알장전", "sound/enemySound/에너미/폿/총알장전.wav", false, false);
	SOUNDMANAGER->addSound("총알터짐", "sound/enemySound/에너미/폿/총알터짐.wav", false, false);

	//슬라임
	SOUNDMANAGER->addSound("슬라임맞음", "sound/enemySound/에너미/슬라임/슬라임맞음.wav", false, false);
	SOUNDMANAGER->addSound("슬라임어텍", "sound/enemySound/에너미/슬라임/슬라임어텍.wav", false, false);
	SOUNDMANAGER->addSound("슬라임죽음", "sound/enemySound/에너미/슬라임/슬라임죽음.wav", false, false);
	SOUNDMANAGER->addSound("슬라임펑", "sound/enemySound/에너미/슬라임/슬라임터트리는공격.wav", false, false);
	SOUNDMANAGER->addSound("레드슬라임공격", "sound/enemySound/에너미/슬라임/레드슬라임공격.wav", false, false);

	//골렘
	SOUNDMANAGER->addSound("골렘공격", "sound/enemySound/에너미/골렘/골렘공격.wav", false, false);
	SOUNDMANAGER->addSound("골렘맞음", "sound/enemySound/에너미/골렘/골렘맞음.wav", false, false);

	//보스
	SOUNDMANAGER->addSound("끌어당김", "sound/enemySound/에너미/보스/끌어당김.wav", false, false);
	SOUNDMANAGER->addSound("돌떨어짐", "sound/enemySound/에너미/보스/돌떨어짐.wav", false, false);
	SOUNDMANAGER->addSound("돌떨어짐2", "sound/enemySound/에너미/보스/돌떨어짐2.wav", false, false);
	SOUNDMANAGER->addSound("보스처음등장", "sound/enemySound/에너미/보스/보스처음등장.wav", false, false);
	SOUNDMANAGER->addSound("보스맞음", "sound/enemySound/에너미/보스/보스맞음.wav", false, false);
	SOUNDMANAGER->addSound("보스죽음", "sound/enemySound/에너미/보스/보스죽음.wav", false, false);
	SOUNDMANAGER->addSound("손떨어짐", "sound/enemySound/에너미/보스/손떨어짐.wav", false, false);
	SOUNDMANAGER->addSound("손빧음", "sound/enemySound/에너미/보스/손빧음.wav", false, false);
	SOUNDMANAGER->addSound("폭발", "sound/enemySound/에너미/보스/폭발.wav", false, false);
	SOUNDMANAGER->addSound("돌사라짐", "sound/enemySound/에너미/보스/돌사라짐.wav", false, false);

	//===========================================↓↓인벤토리↓↓===========================================//

	SOUNDMANAGER->addSound("click", "sound/UI&inventorySound/click.wav", false, false);
	SOUNDMANAGER->addSound("errorItem", "sound/UI&inventorySound/errorItem.wav", false, false);
	SOUNDMANAGER->addSound("gameStart", "sound/UI&inventorySound/gameStart.wav", false, false);
	SOUNDMANAGER->addSound("openInven", "sound/UI&inventorySound/openInven.wav", false, false);
	SOUNDMANAGER->addSound("putItem", "sound/UI&inventorySound/putItem.wav", false, false);
	SOUNDMANAGER->addSound("selectItem", "sound/UI&inventorySound/selectItem.wav", false, false);
}
