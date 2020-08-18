#include "stdafx.h"
#include "UI.h"
#include "player.h"
#include "boss.h"

HRESULT UI::init()
{
	_pendant = ImageManager::GetInstance()->FindImage("UI_pendant");
	_pendantRing = ImageManager::GetInstance()->FindImage("UI_pendant_ring");
	_playerHpImg = ImageManager::GetInstance()->FindImage("HPbar");
	_bossHpImg = ImageManager::GetInstance()->FindImage("boss_HP");

	_hpWidth = 35;
	_bossHpWidth = 38;

	_backBar = RectMakePivot(Vector2(223, 40), Vector2(193, 35), Pivot::LeftTop);
	_HpBar = RectMakePivot(Vector2(223, 40), Vector2(193, (int)_hpWidth), Pivot::LeftTop);

	_weapon = RectMakePivot(Vector2(1456, 119), Vector2(98, 98), Pivot::LeftTop);
	_portal = RectMakePivot(Vector2(1458, 778), Vector2(100, 100), Pivot::LeftTop);

	_bossHpBar = RectMakePivot(Vector2(WINSIZEX / 2, 800), Vector2(1094, (int)_bossHpWidth), Pivot::Center);

	_scene = CURRENT_SCENE::TEMP;

	_frameCount = 0;
	_frameY = 0;

	return S_OK;
}

void UI::render()
{
	//UI밑바탕
	ImageManager::GetInstance()->FindImage("UI_base")->Render(Vector2(0, 0));

	//HP바
	//D2DRenderer::GetInstance()->DrawRectangle(_backBar, D2DRenderer::DefaultBrush::White, 1.f);
	//D2DRenderer::GetInstance()->DrawRectangle(_HpBar, D2DRenderer::DefaultBrush::White, 1.f);
	_playerHpImg->FrameRender(Vector2(_backBar.GetCenter().x, _backBar.GetCenter().y), 0, _frameY, _hpWidth, 35);

	//무기 자리 렉트
	//D2DRenderer::GetInstance()->DrawRectangle(_weapon, D2DRenderer::DefaultBrush::White, 1.f);
	
	//플레이어 기본무기
	if (!_player->getWeaponChange())
	{
		ImageManager::GetInstance()->FindImage("sword")->Render(Vector2(_weapon.left + 15, _weapon.top + 15));
		ImageManager::GetInstance()->FindImage("UI_weapon_1")->Render(Vector2(0, 0));
	}

	//플레이어 서브무기
	if (_player->getWeaponChange())
	{
		ImageManager::GetInstance()->FindImage("bow")->Render(Vector2(_weapon.left + 15, _weapon.top + 10));
		ImageManager::GetInstance()->FindImage("UI_weapon_2")->Render(Vector2(0, 0));
	}

	//펜던트 자리 렉트
	//D2DRenderer::GetInstance()->DrawRectangle(_portal, D2DRenderer::DefaultBrush::White, 1.f);

	//펜던트
	_pendant->Render(Vector2(_portal.left - 30, _portal.top - 15));
	//UI가장 앞
	ImageManager::GetInstance()->FindImage("UI_front")->Render(Vector2(0, 0));	
	
	//돈주머니
	ImageManager::GetInstance()->FindImage("moneyBag")->FrameRender(Vector2(90, 88), 0, _moneyFrameY);
	//소지금
	D2DRenderer::GetInstance()->RenderText(100, 150, to_wstring(INVENTORY->getGold()), 20, D2DRenderer::DefaultBrush::Black);

	if (_bossStage == BOSS_STAGE::STAGE_START)
	{
		//보스 hp바
		//D2DRenderer::GetInstance()->DrawRectangle(_bossHpBar, D2DRenderer::DefaultBrush::White, 1.f);
		ImageManager::GetInstance()->FindImage("boss_bar")->Render(Vector2(_bossHpBar.left, _bossHpBar.top));
		ImageManager::GetInstance()->FindImage("boss_HP")->FrameRender(Vector2(_bossHpBar.GetCenter().x - 2, _bossHpBar.GetCenter().y), 0, _bossFrameY);
	}	

	//장비창 포션 자리가 비어있지 않다면
	if (INVENTORY->getPotion().item != nullptr)
	{
		//포션과 개수 렌더
		INVENTORY->getPotion().item->getImg()->Render(Vector2(1550, 60));
		D2DRenderer::GetInstance()->RenderText(1567, 67, to_wstring(INVENTORY->getPotion().count), 20);
	}

	//인벤토리 열면 수첩 렌더
	if (_scene == CURRENT_SCENE::INVENTORY_OPEN)
	{
		ImageManager::GetInstance()->FindImage("note")->Render(Vector2(WINSIZEX / 2 - 600, WINSIZEY / 2 - 350));
	}

	if (_player->getHitCondition())
	{
		ImageManager::GetInstance()->FindImage("hit_screen")->Render(Vector2(0, 0));
	}
}

void UI::update()
{
	_HpBar = RectMakePivot(Vector2(223, 40), Vector2(193, (int)_hpWidth), Pivot::LeftTop);

	if (_player->getHitCondition())
	{
		_isHit = true;
	}

	/*if (보스 힛)
	{
		_bossHit = true;
	}*/

	_frameCount++;
	draw();	

	setPlayerHpBar();
	setMoneyBag();
}

void UI::release()
{
}

void UI::setPlayerHpBar()
{	
	//_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
	_hpWidth = (_player->getplayerCurrentHp() / 100) * _HpBar.GetWidth();
}

void UI::setBossHpBar(int bossHp)
{

}

void UI::draw()
{	
	if (_frameCount % 3 == 0)
	{
		if (_isHit)
		{
			_frameY++;
			if (_frameY >= _playerHpImg->GetMaxFrameY())
			{
				_isHit = false;
				_frameY = 0;
			}
		}			

		if (_bossHit)
		{
			_bossFrameY++;
			if (_bossFrameY >= _bossHpImg->GetMaxFrameX())
			{
				_bossFrameY = 0;
				_bossHit = false;
			}
		}		
		_frameCount = 0;
	}	
}

void UI::setMoneyBag()
{
	if (INVENTORY->getGold() >= 0 && INVENTORY->getGold() < 5000) _moneyFrameY = 0;
	if (INVENTORY->getGold() >= 5000 && INVENTORY->getGold() < 20000) _moneyFrameY = 1;
	if (INVENTORY->getGold() >= 20000 && INVENTORY->getGold() < 50000) _moneyFrameY = 2;
	if (INVENTORY->getGold() >= 50000 && INVENTORY->getGold() < 100000) _moneyFrameY = 3;
	if (INVENTORY->getGold() >= 100000 && INVENTORY->getGold() < 200000) _moneyFrameY = 4;
	if (INVENTORY->getGold() >= 200000 && INVENTORY->getGold() < 500000) _moneyFrameY = 5;
}
