#pragma once
#include "gameNode.h"

enum class CURRENT_SCENE
{
	TEMP,						//UI�� ����� �ʴ� ����
	INVENTORY,					//�κ��丮 ������ ��
	SHOP_SALE					//������ ���� ����� ��
};

class player;
class inventory;

class UI : public gameNode
{
private:
	CURRENT_SCENE _scene;

	Image* _firstWeapon;					//ù ��° ���� ���ý� UI 
	Image* _secondWeapon;					//�� ��° ���� ���ý� UI
	Image* _pendant;						//������ �ϴ� ���Ʈ
	Image* _pendantRing;					//��� ���� �˸�

	Image* _currentWeapon;					//���� ��� �ִ� ����
	Image* _subWeapon;						//�� ��° ĭ ����
	Image* _HPbar;							//ü�¹�

	FloatRect _weapon;						//���� ��ġ
	FloatRect _portal;						//���Ʈ ��ġ

	int _count;								//���Ʈ Ȱ��ȭ�� ������ �ð�
	bool _weaponChange;						//���� UI �ٲ� �뵵

	player* _player;
	inventory* _inven;

public:
	UI() {}
	~UI() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void setUIHp(int playerHp);

public:
	CURRENT_SCENE getUIScene() { return _scene; }							//���� UI �� ��������
	bool getWeaponChange() { return _weaponChange; }						//���� ���� � �������� ��������

public:
	void setUIScene(CURRENT_SCENE scene) { _scene = scene; }				//���� UI �� �����ֱ�
	void setWeaponChagne(BOOL change = FALSE) { _weaponChange = change; }	//�÷��̾� ������ �����ؼ� �������ֱ�

public:
	//�÷��̾� ������
	void getPlayerMemoryAddressLink(player* player) { _player = player; }
	//�κ��丮 ������
	void getInvenMemoryAddressLink(inventory* inven) { _inven = inven; }
};

