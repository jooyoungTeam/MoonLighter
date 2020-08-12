#pragma once
#include "gameNode.h"

enum class CURRENT_SCENE
{
	TEMP,						//UI�� ����� �ʴ� ����
	INVENTORY_OPEN,				//�κ��丮 ������ ��
	SHOP_SALE					//������ ���� ����� ��
};

class player;

class UI : public gameNode
{
private:
	CURRENT_SCENE _scene;					//���� �� UI ����

	Image* _firstWeapon;					//ù ��° ���� ���ý� UI 
	Image* _secondWeapon;					//�� ��° ���� ���ý� UI
	Image* _pendant;						//������ �ϴ� ���Ʈ
	Image* _pendantRing;					//��� ���� �˸�

	Image* _currentWeapon;					//���� ��� �ִ� ����
	Image* _subWeapon;						//�� ��° ĭ ����
	Image* _HpBarImg;						//ü�¹�

	FloatRect _weapon;						//���� ��ġ
	FloatRect _portal;						//���Ʈ ��ġ
	FloatRect _backBar;						//HP�� ���� ��Ʈ
	FloatRect _HpBar;						//HP�� ��Ʈ

	int _count;								//���Ʈ Ȱ��ȭ�� ������ �ð�
	int _frameCount;						//�¾��� �� HP�� ������ ���� �ð�
	int _frameY;							//HP�� ������Y
	bool _isHit;							//�÷��̾� �¾Ҵ�(���߿� �÷��̾����׼� ������ ����)

	player* _player;

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

public:
	void setUIScene(CURRENT_SCENE scene) { _scene = scene; }				//���� UI �� �����ֱ�
	void setHit(BOOL hit = FALSE) { _isHit = hit; }							//�׽�Ʈ�� hit �� �����ֱ�

public:
	//�÷��̾� ������
	void getPlayerMemoryAddressLink(player* player) { _player = player; }
};

