#pragma once
#include "gameNode.h"

enum class CURRENT_SCENE
{
	TEMP,						//UI�� ����� �ʴ� ����
	INVENTORY_OPEN,				//�κ��丮 ������ ��
	SHOP_SALE					//������ ���� ����� ��
};

enum class BOSS_STAGE
{
	NOT_BOSS,
	PLAYER_ENTER,				//�÷��̾� ���� �������� ����
	BOSS_APEEAR,
	STAGE_START					//���� �������� ���� (�κ��丮 ��� ����?)
};

class player;
class boss;

class UI : public gameNode
{
private:
	CURRENT_SCENE _scene;					//���� �� UI ����
	BOSS_STAGE _bossStage;					//���� UI ����

	Image* _pendant;						//������ �ϴ� ���Ʈ
	Image* _pendantRing;					//��� ���� �˸�

	Image* _playerHpImg;					//�÷��̾�ü�¹�
	Image* _bossHpImg;						//����ü�¹�

	FloatRect _weapon;						//���� ��ġ
	FloatRect _portal;						//���Ʈ ��ġ
	FloatRect _backBar;						//HP�� ���� ��Ʈ
	FloatRect _HpBar;						//HP�� ��Ʈ
	FloatRect _bossBackBar;					//���� HP�� ���� ��Ʈ
	FloatRect _bossHpBar;					//���� HP�� ��Ʈ

	int _count;								//���Ʈ Ȱ��ȭ�� ������ �ð�
	int _bossCount;							//���� �� ���� �� �� �ð�
	int _alphaCount;						//�÷��̾� hit �� �� ȭ�� �����̴� ����ī��Ʈ
	int _frameCount;						//�¾��� �� HP�� ������ ���� �ð�
	int _frameY;							//HP�� ������Y
	int _bossFrameY;						//����HP�� ������Y
	int _moneyFrameY;						//���ָӴ� ������Y

	float _hpWidth;							//�÷��̾� ü�¹� �ʺ�
	float _bossHpWidth;						//���� ü�¹� �ʺ�
	float _alpha;

	bool _isHit;							//�÷��̾� ���� ��
	bool _bossHit;							//���� ���� ��

	player* _player;
	boss* _boss;

public:
	UI() {}
	~UI() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void setPlayerHpBar();
	void setBossHpBar();
	void draw();
	void setMoneyBag();

public:
	CURRENT_SCENE getUIScene() { return _scene; }							//���� UI �� ��������
	BOSS_STAGE getBossScene() { return _bossStage; }						//���� ���� �� ��������

public:
	void setUIScene(CURRENT_SCENE scene) { _scene = scene; }				//���� UI �� �����ֱ�
	void setBossScene(BOSS_STAGE stage) { _bossStage = stage; }				//���� ���� �� �����ֱ�
	void setBossY(int y) { _bossFrameY = y; }								//�ӽ�
	void setAlpha(float a) { _alpha = a; }

public:
	//�÷��̾� ������
	void getPlayerMemoryAddressLink(player* player) { _player = player; }
	//���� ������
	void getBossMemoryAddressLink(boss* boss) { _boss = boss; }
};

