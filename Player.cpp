#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	ptPos1 = { WINSIZE_X / 2, WINSIZE_Y - 30 };

	fMoveSpeed = 20;
}

void Player::Update()
{	/*
		GetAsyncKeyState() : ȣ��� ������ Ű �Է� ���¸� Ȯ���ϴ� �Լ�
		
		�ɼ�
		0x0001 : ������ �������� �ִ°�
		0x8000 : ȣ������� �����ִ°�?
		
		0x0000 : ������ �������� ���� ȣ��������� ���� ���� ����
		0x0001 : ������ �������� �ְ� ȣ��������� ���� ���� ����
		0x8000 : ������ �������� ���� ȣ��������� ��������
		0x8001 : ������ �������� �ְ� ȣ��������� ��������
	*/

	if (KeyManager::Get().IsDown(VK_LEFT)
		||KeyManager::Get().IsState(VK_LEFT))
	{
		if (rtBox1.left - fMoveSpeed >= 0) ptPos1.x -= fMoveSpeed;
	}

	if (KeyManager::Get().IsDown(VK_RIGHT)
		|| KeyManager::Get().IsState(VK_RIGHT))
	{
		if (rtBox1.right + fMoveSpeed <= WINSIZE_X) ptPos1.x += fMoveSpeed;
	}
	rtBox1 = RECT_MAKE(ptPos1.x, ptPos1.y, 50);
}

void Player::Render()
{
	RECT_DRAW(rtBox1);
}
