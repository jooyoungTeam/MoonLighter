#pragma once
#include "gameNode.h"

class player;

class UI : public gameNode
{
private:
	Image* _firstWeapon;					//ù ��° ���� ���ý� UI 
	Image* _secondWeapon;					//�� ��° ���� ���ý� UI
	Image* _pendant;						//������ �ϴ� ���Ʈ
	Image* _pendantRing;					//��� ���� �˸�

	Image* _currentWeapon;
	Image* _subWeapon;
	Image* _HPbar;

	FloatRect _weapon;						//���� ��ġ
	FloatRect _portal;						//���Ʈ ��ġ

	int _count;								//���Ʈ Ȱ��ȭ�� ������ �ð�
	bool _weaponChange;						//���� UI �ٲ� �뵵

	player* _player;

public:
	UI() {}
	~UI() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void setUIHp();

public:
	bool getWeaponChange() { return _weaponChange; }

public:
	void setWeaponChagne(BOOL change = FALSE) { _weaponChange = change; }

public:
	//�÷��̾� ������
	void getPlayerMemoryAddressLink(player* inven) { _player = inven; }
};

