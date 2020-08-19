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

	_backBar = RectMakePivot(Vector2(223, 40), Vector2(193, 35), Pivot::LeftTop);
	_HpBar = RectMakePivot(Vector2(223, 40), Vector2(193, 35), Pivot::LeftTop);

	_weapon = RectMakePivot(Vector2(1456, 119), Vector2(98, 98), Pivot::LeftTop);
	_portal = RectMakePivot(Vector2(1458, 778), Vector2(100, 100), Pivot::LeftTop);

	_bossBackBar = RectMakePivot(Vector2(WINSIZEX / 2, 800), Vector2(1094, 38), Pivot::Center);
	_bossHpBar = RectMakePivot(Vector2(WINSIZEX / 2, 800), Vector2(1094, 38), Pivot::Center);

	_scene = CURRENT_SCENE::TEMP;
	_bossStage == BOSS_STAGE::NOT_BOSS;

	_frameCount = 0;
	_frameY = 0;
	_bossFrameY = 0;
	_moneyFrameY = 0;
	_alpha = 1.f;

	_isHit = false;
	_bossHit = false;


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

	if (_bossStage == BOSS_STAGE::PLAYER_ENTER)
	{
		ImageManager::GetInstance()->FindImage("boss_scroll")->SetAlpha(_alpha);
		ImageManager::GetInstance()->FindImage("boss_scroll")->FrameRender(Vector2(WINSIZEX / 2, WINSIZEY / 2 + 100), 0, _bossFrameY);
	}

	if (_bossStage == BOSS_STAGE::BOSS_APEEAR || _bossStage == BOSS_STAGE::STAGE_START)
	{
		//보스 hp바
		//D2DRenderer::GetInstance()->DrawRectangle(_bossHpBar, D2DRenderer::DefaultBrush::White, 1.f);
		ImageManager::GetInstance()->FindImage("boss_bar")->Render(Vector2(_bossBackBar.left, _bossBackBar.top));
		ImageManager::GetInstance()->FindImage("boss_HP")->FrameRender(Vector2(_bossBackBar.GetCenter().x - 2, _bossBackBar.GetCenter().y), 0, _bossFrameY, _bossHpWidth, 38);
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

	//플레이어 맞을 때 화면 깜박임
	if (_alphaCount == 1 && _player->getHitCondition())
	{
		ImageManager::GetInstance()->FindImage("hit_screen")->SetAlpha(0.5);
		ImageManager::GetInstance()->FindImage("hit_screen")->Render(Vector2(0, 0));
	}	
}

void UI::update()
{
	_frameCount++;
	draw();	

	_HpBar = RectMakePivot(Vector2(223, 40), Vector2(193, (int)_hpWidth), Pivot::LeftTop);
	//_bossHpBar = RectMakePivot(Vector2(WINSIZEX / 2, 800), Vector2(1094, (int)_bossHpWidth), Pivot::LeftTop);

	if (_player->getHitCondition())
	{
		_isHit = true;
		_alphaCount++;
	}

	if (!_player->getHitCondition())
	{
		_alphaCount = 0;
	}

	/*if (_boss->getIsHit())
	{
		_bossHit = true;
	}*/

	if (_bossStage == BOSS_STAGE::PLAYER_ENTER)
	{
		_bossCount++;
	}

	if (_bossCount > 500)
	{
		_bossStage = BOSS_STAGE::STAGE_START;
	}

	setPlayerHpBar();
	//setBossHpBar();
	setMoneyBag();
}

void UI::release()
{
}

void UI::setPlayerHpBar()
{
	if (_player->getplayerCurrentHp() <= 0) _hpWidth = 0;
	_hpWidth = (_player->getplayerCurrentHp() / _player->getPlayerMaxHp()) * _HpBar.GetWidth();
}

void UI::setBossHpBar()
{
	if (_boss->getCurHP() <= 0) _bossHpWidth = 0;
	_bossHpWidth = (_boss->getCurHP() / 100) * _bossHpWidth;
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

void UI::draw()
{	
	if (_frameCount % 3 == 0)
	{
		if (_isHit)
		{
			_frameY++;
			if (_frameY >= _playerHpImg->GetMaxFrameY())
			{
				_frameY = 0;
				_isHit = false;
			}
		}		

		if (_bossHit)
		{
			_bossFrameY++;
			if (_bossFrameY >= _bossHpImg->GetMaxFrameY())
			{
				_bossFrameY = 0;
				_bossHit = false;
			}
		}	
	}	

	if (_frameCount % 5 == 0)
	{
		if (_bossStage == BOSS_STAGE::PLAYER_ENTER)
		{
			_bossFrameY++;
			if (_bossFrameY >= 8)
			{
				_bossFrameY = 8;
				_alpha -= 0.03;

				if (_alpha <= 0)
				{
					_bossFrameY = 0;
					_bossStage = BOSS_STAGE::BOSS_APEEAR;
				}
			}
		}
		_frameCount = 0;
	}
}
