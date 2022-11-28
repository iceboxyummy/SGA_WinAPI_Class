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
	// InvalidateRect : 화면을 갱신해주는 함수 ( true : 해당 영역을 지우고 다시 그린다. false : 해당 영역을 지우지 않고 덮어씌운다.)
	InvalidateRect(g_hWnd, NULL, true); // NULL일 경우 모든 영역을 갱신한다.

	/*
		GetAsyncKeyState() : 호출된 시점의 키 입력 상태를 확인하는 함수
		
		옵션
		0x0001 : 이전에 누른적이 있는가
		0x8000 : 호출시점에 눌려있는가?
		
		0x0000 : 이전에 누른적이 없고 호출시점에도 눌려 있지 않음
		0x0001 : 이전에 누른적이 있고 호출시점에는 눌려 있지 않음
		0x8000 : 이전에 누른적이 없고 호출시점에는 눌려있음
		0x8001 : 이전에 누른적이 있고 호출시점에도 눌려있음
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

	// 상자생성
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

	// 상자 하강
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

		// dc(device context) : 출력을 위한 모든 데이터를 가지는 구조체
		HDC hdc = BeginPaint(g_hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.

		RECT_DRAW(rtBox1);

		for (const auto& box : vecBox)
			RECT_DRAW(box.rt);

		wstring wScore(to_wstring(nScore).c_str());
		TextOut(hdc, 10, 10, wScore.c_str(), wScore.length());

		wstring nLevel(to_wstring(nLevel).c_str());
		TextOut(hdc, 10, 310, nLevel.c_str(), nLevel.length());

		EndPaint(g_hWnd, &ps);
}