#include "stdafx.h"
#include "UI.h"

HRESULT UI::init()
{
	ImageManager::GetInstance()->AddImage("UI_base", L"Image/UI/UI_base.png");
	_firstWeapon = ImageManager::GetInstance()->AddImage("UI_weapon_1", L"Image/UI/UI_weapon_1.png");
	_secondWeapon = ImageManager::GetInstance()->AddImage("UI_weapon_2", L"Image/UI/UI_weapon_2.png");
	_pendant = ImageManager::GetInstance()->AddImage("UI_pendant", L"image/UI/UI_pendant.png");
	_pendantRing = ImageManager::GetInstance()->AddImage("UI_pendant_ring", L"Image/UI/UI_pendant_ring.png");
	ImageManager::GetInstance()->AddImage("UI_front", L"Image/UI/UI_front.png");

	_weapon = RectMakePivot(Vector2(1456, 119), Vector2(98, 98), Pivot::LeftTop);
	_portal = RectMakePivot(Vector2(1458, 778), Vector2(100, 100), Pivot::LeftTop);

	_weaponChange = false;

	return S_OK;
}

void UI::render()
{
	ImageManager::GetInstance()->FindImage("UI_base")->Render(Vector2(0, 0));
	D2DRenderer::GetInstance()->DrawRectangle(_weapon, D2DRenderer::DefaultBrush::White, 1.f);

	if (!_weaponChange) _firstWeapon->Render(Vector2(0, 0));
	if (_weaponChange) _secondWeapon->Render(Vector2(0, 0));

	D2DRenderer::GetInstance()->DrawRectangle(_portal, D2DRenderer::DefaultBrush::White, 1.f);

	_pendant->Render(Vector2(_portal.left - 30, _portal.top - 15));
	ImageManager::GetInstance()->FindImage("UI_front")->Render(Vector2(0, 0));
}

void UI::update()
{

}

void UI::release()
{
}

void UI::setUIHp()
{
}
