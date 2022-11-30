// �ñ������� http://soen.kr/ ���� Ȯ���غ���.

// WinAPI.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.

/*
	WIN API, WIN SDK (Windows Application Program Interface) : �����츦 �����ϴµ� ����ϴ� �Լ��� ����, ��� ������

	Windows : �ü��
	API : �ü���� �����ϴ� ���� ���α׷��� ����� ���� �Լ��� ����
*/

#include "stdafx.h"
#include "WinAPI.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING] = PROGRAM_TITLE;  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND g_hWnd;
POINT g_ptMouse;
HDC g_hDC;

MainGame* pMainGame = nullptr;

/*
	Handle : �ü�� ���ο� �ִ� ���ҽ�(�ڿ�)�� �ּҸ� ������ ġȯ�� ��
	 - �ڵ� ���̺��� �ڵ�� ���ҽ��� �ּҰ� �����ȴ�.

	 Resource : ���� �ϵ���� ��ġ �Ǵ� ������ġ(�޸�, �ϵ� ��)�� ����ִ� ������ �ڷ�
	 Instance Handle : �����쿡�� ���� �������� ���μ����� �ڵ��� ����Ű�� ��
*/

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // ���α׷� �ڵ� �ν��Ͻ�
	_In_opt_ HINSTANCE hPrevInstance,					// ������ ����� �ڵ� �ν��Ͻ�
	_In_ LPWSTR    lpCmdLine,						    // cmd�� �Էµ� ���α׷� �μ� - ������ �� ���α׷��� �ʱ⼳�� ���氡��
	_In_ int       nCmdShow)						    // ���α׷��� ���� �� �� ����(�ּ�ȭ ���� ���� ���°�)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.

	// LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���ø����̼� �ʱ�ȭ�� �����մϴ�:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// ����Ű(����������) ���̺��� �д´�.
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

	MSG msg;

	pMainGame = new MainGame;
	pMainGame->Init();
	KeyManager::Get().Init();

	HDC hdc = GetDC(g_hWnd);
	// ���� DC�� ����Ͽ� �߰��� DC�� �����Ѵ�.
	g_hDC = CreateCompatibleDC(hdc);
	// ����۷� ����� ��Ʈ���� �����Ѵ�.
	// ��Ʈ�� : �ȼ� �̹����� �����ϴ� �������� �Ǵ� ���� ���
	HBITMAP hBitmap = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZE_X, WINSIZE_Y);
	// ����� DC�� ��Ʈ�� ����
	SelectObject(g_hDC, hBitmap);

	// �⺻ �޽��� �����Դϴ�.
	//while (GetMessage(&msg, nullptr, 0, 0)) // GetMessage : �޽��� ť���� �޽����� �д´�.
	//{
	//	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	//	{
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);
	//	}
	//}

	while(true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			if (pMainGame != nullptr)
			{
				pMainGame->Update();
				pMainGame->Render();
			}
		}
	}

	delete pMainGame;

	return (int)msg.wParam;
}

//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	// �������� ������ �����ϴ� ����ü �ڷ���
	// â�� ������� ����������� ���� �ۼ��Ѵ�.
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // ����ü�� ũ�������� ����ش�.

	wcex.style = CS_HREDRAW | CS_VREDRAW;                                   // ������ ��Ÿ��                                            
			  // CS_HREDRAW | CS_VREDRAW : ����, ���� ũ�� ����� â�� �ٽ� �׸���.
	wcex.lpfnWndProc = WndProc;                                             // �޽��� ó�� �Լ� ����
	wcex.cbClsExtra = 0;                                                    // Ŭ���� ���� �޸�
	wcex.cbWndExtra = 0;                                                    // ������ ���� �޸�
	wcex.hInstance = hInstance;												// �ν��Ͻ�
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));			// â�� ������
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);						    // ���콺 Ŀ��
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);					    // ����
	wcex.lpszMenuName = NULL;												// �޴� �̸�(NULL�Ͻ� �޴� ����)
	wcex.lpszClassName = szWindowClass;										// Ŭ���� �̸�
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));	// ���� ������        

	// ������ Ŭ���� ���
	return RegisterClassExW(&wcex);
}

//   �Լ� : InitInstance(HINSTANCE, int)
//
//   �뵵 : �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ� : �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ� �� ���α׷� â�� ���� ���� ǥ���մϴ�.

// â�� �ʱ�ȭ�ϰ� �������ִ� �κ�
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	// ȭ�� �ػ� �ޱ�
	int nResolutionX = GetSystemMetrics(SM_CXSCREEN);
	int nResolutionY = GetSystemMetrics(SM_CYSCREEN);

	// â ȭ�� �߾� ��ġ ���(���������)
	int nWinPosX = nResolutionX / 2 - WINSIZE_X / 2;
	int nWinPosY = nResolutionY / 2 - WINSIZE_Y / 2;

	// â�� �����ϰ� �����Ѵ�.
	HWND hWnd = CreateWindowW(
		szWindowClass,        // ������ Ŭ���� �̸�
		szTitle,              // Ÿ��Ʋ�� �̸�  
		WS_OVERLAPPEDWINDOW,  // ������ ��Ÿ��
		nWinPosX,             // ������ ȭ�� ��ǥ x : ������ �� �����ġ���� ��������
		nWinPosY,             // ������ ȭ�� ��ǥ Y
		WINSIZE_X,            // ������ ���� ������
		WINSIZE_Y,            // ������ ���� ������
		nullptr,              // �θ� ������
		nullptr,              // �޴� �ڵ�
		hInstance,            // �ν��Ͻ� ����
		nullptr               // �ڽ� �����츦 �����ϸ� ���� ���ٸ� NULL
	);

	if (!hWnd)
	{
		return FALSE;
	}

	g_hWnd = hWnd;

	// ������ ������ ����(Ÿ��Ʋ �� �� �޴��� �ǻ������ ����)
	{
		// ���ϴ� �۾� ����
		RECT rt = { nWinPosX,nWinPosY, nWinPosX + WINSIZE_X, nWinPosY + WINSIZE_Y };

		// ���ϴ� �۾����� ũ��, ��Ÿ�� ��, �޴��� ���θ� �ѱ��
		// ���ϴ� �۾������� �´� ������ ũ�⸦ ����� rt�� �־��ش�.
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

		MoveWindow(
			hWnd,
			nWinPosX,			// x
			nWinPosY,			// y
			rt.right - rt.left,	// �ʺ�
			rt.bottom - rt.top,	// ����
			TRUE				// â�� ���� �׸� ���ΰ�?
		);
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.

/*
	Proc : �޽��� ó���Լ�
	 - window api�� �޽������ ���α׷����̴�.
	 - �޽����� �ٷ� �� �Ŵ��� �޽��� ť�� ����Ѵ�. (�����Ǵ� �޽����� ���ʴ�� ó�����ش�.) ex) �Է�, â ����
	   -> �������� ���� �޽����� �տ� �޽����� ó���� ������ ������ �� ������ �����̰� ���� �� �ִ�.
	 - api�� �⺻���� â����, ���콺 ó�� �뵵 �����θ� ����Ѵ�.
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_CREATE: // �����찡 ������ �� 1�� ȣ���� �Ǵ� �޽���
	{
		// Ÿ�̸� : �����ֱ⸶�� �޽��� ȣ���� ���ػ���Ѵ�.
		// ȣ���� �Լ��� NULL�� ������ ��� VM_TIMER �޽����� �߻���Ų��.
		// SetTimer(hWnd, 1, 10, NULL); // �ڵ�, Ÿ�̸� �ѹ�, ȣ�� �ֱ� 1 == 1/1000��

		srand(time(NULL));
		break;
	}

	//case WM_TIMER: // Ÿ�̸Ӱ� ���൹ �� ȣ��Ǵ� �޽���
	//{
	//	KeyManager::Get().update();
	//	if(pMainGame != nullptr)
	//		pMainGame->Update();
	//	break;
	//}

	case WM_MOUSEMOVE: // ���콺�� �̵��� �� �߻��ϴ� �޽���
	{
		// lParam : WM_MOUSEMOVE���� ���콺 ��ǥ���� ���
		// LOWORD(), HIWORD()�� ��Ʈ�������� ������ ��ġ�� �ִ� ��Ʈ���� �޾ƿ´�.

		g_ptMouse.x = LOWORD(lParam); // ���� ��Ʈ�� x ��ǥ���� ����
		g_ptMouse.y = LOWORD(lParam); // ���� ��Ʈ�� y ��ǥ���� ����

		break;
	}

	/*case WM_PAINT:
	{
		if (pMainGame != nullptr)
			pMainGame->Render();
		break;
	}*/
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}