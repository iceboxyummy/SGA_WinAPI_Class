// 궁금한점은 http://soen.kr/ 에서 확인해보자.

// WinAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.

/*
    WIN API, WIN SDK (Windows Application Program Interface) : 윈도우를 개발하는데 사용하는 함수의 집합, 기능 모음집

    Windows : 운영체제
    API : 운영체제가 제공하는 응용 프로그렘을 만들기 위한 함수의 집합
*/

#include "stdafx.h"
#include "WinAPI.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING] = PROGRAM_TITLE;  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

/*
    Handle : 운영체제 내부에 있는 리소스(자원)의 주소를 정수로 치환한 값
     - 핸들 테이블에서 핸들과 리소스의 주소가 관리된다.

     Resource : 각종 하드웨어 장치 또는 저장장치(메모리, 하드 등)에 들어있는 데이터 자료
     Instance Handle : 윈도우에서 현재 실행중인 프로세서의 핸들을 가리키는 것
*/
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // 프로그램 핸들 인스턴스
                     _In_opt_ HINSTANCE hPrevInstance,  // 이전에 실행된 핸들 인스턴스
                     _In_ LPWSTR    lpCmdLine,          // cmd로 입력된 프로그램 인수 - 실행할 때 프로그램의 초기설정 변경가능
                     _In_ int       nCmdShow)           // 프로그램이 시작 될 때 형태(최소화 보통 등의 상태값)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
 
    // LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키(엑셀테이터) 테이블을 읽는다.
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

    MSG msg;

    // 기본 메시지 루프입니다.
    while (GetMessage(&msg, nullptr, 0, 0)) // GetMessage : 메시지 큐에서 메시지를 읽는다.
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // 윈도우의 정보를 저장하는 구조체 자료형
    // 창을 어떤식으로 만들것인지에 대해 작성한다.
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX); // 구조체의 크기정보를 담아준다.

    wcex.style          = CS_HREDRAW | CS_VREDRAW;                              // 윈도우 스타일                                            
                       // CS_HREDRAW | CS_VREDRAW : 가로, 세로 크기 변경시 창을 다시 그린다.
    wcex.lpfnWndProc    = WndProc;                                              // 메시지 처리 함수 지정
    wcex.cbClsExtra     = 0;                                                    // 클래스 여분 메모리
    wcex.cbWndExtra     = 0;                                                    // 윈도우 여분 메모리
    wcex.hInstance      = hInstance;                                            // 인스턴스
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));     // 창의 아이콘
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);                       // 마우스 커서
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);                             // 배경색
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPI);                         // 메뉴 이름(NULL일시 메뉴 제거)
    wcex.lpszClassName  = szWindowClass;                                        // 클래스 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // 작은 아이콘        

    // 윈도우 클래스 등록
    return RegisterClassExW(&wcex);
}

//   함수 : InitInstance(HINSTANCE, int)
//
//   용도 : 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석 : 이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고 주 프로그램 창을 만든 다음 표시합니다.

// 창을 초기화하고 생성해주는 부분
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 화면 해상도 받기
   int nResolutionX = GetSystemMetrics(SM_CXSCREEN);
   int nResolutionY = GetSystemMetrics(SM_CYSCREEN);

   // 창 화면 중앙 위치 계산(좌측상단점)
   int nWinPosX = nResolutionX / 2 - WINSIZE_X / 2;
   int nWinPosY = nResolutionY / 2 - WINSIZE_Y / 2;

   // 창을 생성하고 저장한다.
   HWND hWnd = CreateWindowW( szWindowClass,        // 윈도우 클래스 이름
                              szTitle,              // 타이틀바 이름  
                              WS_OVERLAPPEDWINDOW,  // 윈도우 스타일
                              nWinPosX,             // 윈도우 화면 좌표 x : 실행할 때 어느위치에서 띄울것인지
                              nWinPosY,             // 윈도우 화면 좌표 Y
                              WINSIZE_X,            // 윈도우 가로 사이즈
                              WINSIZE_Y,            // 윈도우 세로 사이즈
                              nullptr,              // 부모 윈도우
                              nullptr,              // 메뉴 핸들
                              hInstance,            // 인스턴스 지정
                              nullptr);             // 자식 윈도우를 생성하면 지정 없다면 NULL

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.

/*
    Proc : 메시지 처리함수
     - window api는 메시지기반 프로그래밍이다.
     - 메시지를 다룰 때 거대한 메시지 큐를 사용한다. (생성되는 메시지를 차례대로 처리해준다.) ex) 입력, 창 변경
       -> 마지막에 들어온 메시지는 앞에 메시지가 처리될 때까지 동작을 할 수없어 딜에이가 있을 수 있다.
     - api는 기본적인 창띄우기, 마우스 처리 용도 정도로만 사용한다.
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
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

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            
            // dc(device context) : 출력을 위한 모든 데이터를 가지는 구조체
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.

            // 문자열 출력
            /*
            wstring wstr = L"안녕 윈도우!!!";

            TextOut(hdc, 10, 10, wstr.c_str(), wstr.length());
            */

            // 선 그리기

            // 선의 시작점 지정
            //MoveToEx(hdc, 50, 50, NULL);

            // 현재 시작점에서 선그리기
            //LineTo(hdc, 100, 50);
            //LineTo(hdc, 100, 70);

            // 사각형그리기
            //Rectangle(hdc, 150, 150, 200, 200);

            // 원그리기
            //Ellipse(hdc, 400, 400, 500, 500);

			// 격자무늬 만들기
            /*
			for (int x = 0; x < WINSIZE_X; x += 50)
			{
				MoveToEx(hdc, x, 0, NULL);
				LineTo(hdc, x, WINSIZE_Y);
			}

			for (int y = 0; y < WINSIZE_Y; y += 50)
            {
                MoveToEx(hdc, 0, y, NULL);
                LineTo(hdc, WINSIZE_X, y);
            }
            */

			// 반목문 하나만 사용해서 도형 번갈아 출력하기
            for (int i = 0; i < 25; i++)
            {
                if ((i / 5) % 2 == 0)
                    Rectangle(hdc, 100 + (i % 5) * 100, 100 + (i / 5) * 100, 150 + (i % 5) * 100, 150 + (i / 5) * 100);

                else if ((i / 5) % 2 == 1)
                    Ellipse(hdc, 100 + (i % 5) * 100, 100 + (i / 5) * 100, 150 + (i % 5) * 100, 150 + (i / 5) * 100);
            }

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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