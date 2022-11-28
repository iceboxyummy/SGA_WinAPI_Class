#include "MainGame.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	ptPos1 = { WINSIZE_X / 2, WINSIZE_Y - 30 };
	vector<tagBox> vecBox;

	fMoveSpeed = 20;

	nScore = 0;
	nLevel = 1;

	nDelay = 50;
}

void MainGame::Update()
{
	// InvalidateRect : ȭ���� �������ִ� �Լ� ( true : �ش� ������ ����� �ٽ� �׸���. false : �ش� ������ ������ �ʰ� ������.)
	InvalidateRect(g_hWnd, NULL, true); // NULL�� ��� ��� ������ �����Ѵ�.

	/*
		GetAsyncKeyState() : ȣ��� ������ Ű �Է� ���¸� Ȯ���ϴ� �Լ�
		
		�ɼ�
		0x0001 : ������ �������� �ִ°�
		0x8000 : ȣ������� �����ִ°�?
		
		0x0000 : ������ �������� ���� ȣ��������� ���� ���� ����
		0x0001 : ������ �������� �ְ� ȣ��������� ���� ���� ����
		0x8000 : ������ �������� ���� ȣ��������� ��������
		0x8001 : ������ �������� �ְ� ȣ��������� ��������
	*/

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (rtBox1.left - fMoveSpeed >= 0) ptPos1.x -= fMoveSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (rtBox1.right + fMoveSpeed <= WINSIZE_X) ptPos1.x += fMoveSpeed;
	}

	nLevel = nScore / 100 + 1;

	rtBox1 = RECT_MAKE(ptPos1.x, ptPos1.y, 50);

	// ���ڻ���
	if (nDelay >= 50)
	{
		tagBox box;

		box.rt.left = rand() % WINSIZE_X;
		box.rt.right = box.rt.left + 30;
		box.rt.top = -30;
		box.rt.bottom = 0;

		box.speed = rand() % 10 + 5;

		vecBox.push_back(box);

		nDelay = rand() % 40;
	}

	else nDelay += nLevel;

	// ���� �ϰ�
	RECT rt;

	for (auto iter = vecBox.begin(); iter != vecBox.end();)
	{
		iter->rt.top += iter->speed + nLevel;
		iter->rt.bottom += iter->speed + nLevel;

		RECT rtIter = iter->rt;

		if (iter->rt.top > WINSIZE_Y)
		{
			nScore += 5;
			iter = vecBox.erase(iter);
		}

		else if (IntersectRect(&rt, &rtIter, &rtBox1))
		{
			nScore -= 20;
			iter = vecBox.erase(iter);
		}

		else if (PtInRect(&rtIter, g_ptMouse))
		{
			nScore += 2;
			iter = vecBox.erase(iter);
		}

		else iter++;
	}
}

void MainGame::Render()
{
		PAINTSTRUCT ps;

		// dc(device context) : ����� ���� ��� �����͸� ������ ����ü
		HDC hdc = BeginPaint(g_hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.

		RECT_DRAW(rtBox1);

		for (const auto& box : vecBox)
			RECT_DRAW(box.rt);

		wstring wScore(to_wstring(nScore).c_str());
		TextOut(hdc, 10, 10, wScore.c_str(), wScore.length());

		wstring nLevel(to_wstring(nLevel).c_str());
		TextOut(hdc, 10, 310, nLevel.c_str(), nLevel.length());

		EndPaint(g_hWnd, &ps);
}