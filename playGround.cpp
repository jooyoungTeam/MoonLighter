#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	gameNode::init(true);

	_stageManager = new stageManager;
	_stageManager->init();

	return S_OK;
}

//�޸� ����
void playGround::release()
{
	_stageManager->release();
}

//����
void playGround::update()
{
	gameNode::update();

	_stageManager->update();
}

//�׸��� ����
void playGround::render()
{
	// ����� �ʱ�ȭ
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::White);
	{
		_stageManager->render();

	}
	// ����ۿ� �׸� ������� ȭ�鿡 �ѷ���.
	D2DRenderer::GetInstance()->EndRender();
}
