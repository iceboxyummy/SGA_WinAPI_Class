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
		GetAsyncKeyState() : 호출된 시점의 키 입력 상태를 확인하는 함수
		
		옵션
		0x0001 : 이전에 누른적이 있는가
		0x8000 : 호출시점에 눌려있는가?
		
		0x0000 : 이전에 누른적이 없고 호출시점에도 눌려 있지 않음
		0x0001 : 이전에 누른적이 있고 호출시점에는 눌려 있지 않음
		0x8000 : 이전에 누른적이 없고 호출시점에는 눌려있음
		0x8001 : 이전에 누른적이 있고 호출시점에도 눌려있음
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
