#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "Object.h"

MainGame::MainGame()
{
	pPlayer = new Player;
	pObject = new Object;
}

MainGame::~MainGame()
{

	if (pObject)
	{
		delete pObject;
		pObject = nullptr;
	}

	if (pPlayer)
	{
		delete pPlayer;
		pPlayer = nullptr;
	}
}

void MainGame::Init()
{
	nScore = 0;
	nLevel = 0;

	if (pPlayer != nullptr)pPlayer->Init();
	if (pObject != nullptr)pObject->Init();
}

void MainGame::Update()
{
	// InvalidateRect : 화면을 갱신해주는 함수 ( true : 해당 영역을 지우고 다시 그린다. false : 해당 영역을 지우지 않고 덮어씌운다.)
	InvalidateRect(g_hWnd, NULL, false); // NULL일 경우 모든 영역을 갱신한다.

	nLevel = nScore / 100 + 1;

	if (pPlayer != nullptr)pPlayer->Update();
	if (pObject != nullptr)
	{
		pObject->SetLevel(nLevel);
		pObject->Update();
	}

	// 상자 하강
	RECT rt;

	for (auto iter = pObject->GetBox().begin(); iter != pObject->GetBox().end();)
	{
		RECT rtIter = iter->rt;

		if (iter->rt.top > WINSIZE_Y)
		{
			nScore += 5;
			iter = pObject->GetBox().erase(iter);
		}

		else if (IntersectRect(&rt, &rtIter, &pPlayer->GetRect()))
		{
			nScore -= 20;
			iter = pObject->GetBox().erase(iter);
		}

		else if (PtInRect(&rtIter, g_ptMouse))
		{
			nScore += 2;
			iter = pObject->GetBox().erase(iter);
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

		// 백버퍼를 흰색으로 초기화
		PatBlt(g_hDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

		// 백버퍼에 그림을 그려준다.
		if (pPlayer != nullptr)pPlayer->Render();
		if (pObject != nullptr)pObject->Render();

		wstring wScore(to_wstring(nScore).c_str());
		TextOut(g_hDC, 10, 10, wScore.c_str(), wScore.length());

		wstring wLevel(to_wstring(nLevel).c_str());
		TextOut(g_hDC, 10, 30, wLevel.c_str(), wLevel.length());

		// 백버퍼에서 그린 이미지를 전면버퍼에 복사해준다.
		BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, g_hDC, 0, 0, SRCCOPY);

		EndPaint(g_hWnd, &ps);
}