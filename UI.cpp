#include "stdafx.h"
#include "UI.h"
#include "inventory.h"

HRESULT UI::init()
{
	ImageManager::GetInstance()->AddImage("UI_base", L"Image/UI/UI_base.png");
	ImageManager::GetInstance()->AddImage("UI_weapon_1", L"Image/UI/UI_weapon_1.png");
	ImageManager::GetInstance()->AddImage("UI_weapon_2", L"Image/UI/UI_weapon_2.png");
	ImageManager::GetInstance()->AddImage("UI_pendant", L"image/UI/UI_pendant.png");
	ImageManager::GetInstance()->AddImage("UI_pendant_ring", L"Image/UI/UI_pendant_ring.png");
	ImageManager::GetInstance()->AddImage("UI_front", L"Image/UI/UI_front.png");
	ImageManager::GetInstance()->AddImage("note", L"image/UI/note.png");
	ImageManager::GetInstance()->AddFrameImage("HPbar", L"Image/UI/HPbar.png", 1, 5);

	_firstWeapon = ImageManager::GetInstance()->FindImage("UI_weapon_1");
	_secondWeapon = ImageManager::GetInstance()->FindImage("UI_weapon_2");
	_pendant = ImageManager::GetInstance()->FindImage("UI_pendant");
	_pendantRing = ImageManager::GetInstance()->FindImage("UI_pendant_ring");
	_HpBarImg = ImageManager::GetInstance()->FindImage("HPbar");

	_backBar = RectMakePivot(Vector2(223, 40), Vector2(193, 35), Pivot::LeftTop);
	_HpBar = RectMakePivot(Vector2(223, 40), Vector2(193, 35), Pivot::LeftTop);

	_weapon = RectMakePivot(Vector2(1456, 119), Vector2(98, 98), Pivot::LeftTop);
	_portal = RectMakePivot(Vector2(1458, 778), Vector2(100, 100), Pivot::LeftTop);

	_scene = CURRENT_SCENE::TEMP;

	_frameCount = 0;
	_frameY = 0;

	return S_OK;
}

void UI::render()
{
	//UI�ع���
	ImageManager::GetInstance()->FindImage("UI_base")->Render(Vector2(0, 0));

	//HP��
	//D2DRenderer::GetInstance()->DrawRectangle(_backBar, D2DRenderer::DefaultBrush::White, 1.f);
	_HpBarImg->FrameRender(Vector2(_backBar.GetCenter().x, _backBar.GetCenter().y), 0, _frameY);

	//���� �ڸ� ��Ʈ
	D2DRenderer::GetInstance()->DrawRectangle(_weapon, D2DRenderer::DefaultBrush::White, 1.f);
	//�÷��̾� ����false
	_firstWeapon->Render(Vector2(0, 0));
	//�÷��̾� ���� true
	//_secondWeapon->Render(Vector2(0, 0));

	//���Ʈ �ڸ� ��Ʈ
	D2DRenderer::GetInstance()->DrawRectangle(_portal, D2DRenderer::DefaultBrush::White, 1.f);

	//���Ʈ
	_pendant->Render(Vector2(_portal.left - 30, _portal.top - 15));
	//UI���� ��
	ImageManager::GetInstance()->FindImage("UI_front")->Render(Vector2(0, 0));	

	//������
	D2DRenderer::GetInstance()->RenderText(100, 150, to_wstring(_inven->getGold()), 20, D2DRenderer::DefaultBrush::Black);

	//���â ���� �ڸ��� ������� �ʴٸ�
	if (_inven->getPotion().item != nullptr)
	{
		//���ǰ� ���� ����
		_inven->getPotion().item->getImg()->Render(Vector2(1550, 60));
		D2DRenderer::GetInstance()->RenderText(1567, 67, to_wstring(_inven->getPotion().count), 20);
	}

	//�κ��丮 ���� ��ø ����
	if (_scene == CURRENT_SCENE::INVENTORY)
	{
		ImageManager::GetInstance()->FindImage("note")->Render(Vector2(WINSIZEX / 2 - 600, WINSIZEY / 2 - 350));
	}
}

void UI::update()
{
	if (_isHit)
	{
		_frameCount++;

		if (_frameCount % 5 == 0)
		{
			_frameY++;
			if (_frameY >= _HpBarImg->GetMaxFrameY())
			{
				_frameY = 0;
				_isHit = false;
			}
			_frameCount = 0;
		}
	}	
}

void UI::release()
{
}

void UI::setUIHp(int playerHp)
{
}
