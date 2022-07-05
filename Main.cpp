#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <CommCtrl.h>

#define IDC_BUTTON1 1001
#define IDC_BUTTON2 1002
#define ID_EDITCHILD 1011

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Tab1Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Tab2Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Tab3Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	//WNDCLASS wc = {};

	//wc.lpfnWndProc = WindowProc;
	//wc.hInstance = hInstance;
	//wc.lpszClassName = CLASS_NAME;
	//wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(145, 167, 255));

	WNDCLASSEXW wcex;

	//wc.style = CS_HREDRAW| CS_VREDRAW;
	//wc.lpfnWndProc = WindowProc;
	//wc.cbClsExtra=0;
	//wc.cbWndExtra=0;
	//wc.hInstance= hInstance;
	//wc.hIcon=NULL;
	//wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	////wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(145, 167, 255));
	//wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//wc.lpszMenuName = NULL;
	//wc.lpszClassName = CLASS_NAME;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	//wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = CLASS_NAME;
	wcex.hIconSm = NULL;
	
	RegisterClassExW(&wcex);

	//RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style
		//WS_CLIPCHILDREN,

										// Size and position
		//CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		0,0,500,300,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
		);

	if (!hwnd)
	{
		MessageBox(NULL, L"Faild to Create Main Window", L"Error!", MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Run the message loop.

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInst;
	const wchar_t TAB_CLASS_NAME[] = L"Tab1 Window Class";
	const wchar_t TAB2_CLASS_NAME[] = L"Tab 2 Window Class";
	const wchar_t TAB3_CLASS_NAME[] = L"Tab 3 Window Class";
	static HWND hwndTab;
	static HWND hTab1Wnd;
	static HWND hTab2Wnd;
	static HWND hTab3Wnd;
	
	RECT rcRect;
	static int top_x = 0;
	static int top_y = 0;
	static int child_width = 0;
	static int child_height = 0;
	WNDCLASS wcex1;

	switch (uMsg)
	{
	
	case WM_CREATE:
	{

		hInst = GetModuleHandle(NULL);
		TCITEM tie;

		hwndTab = CreateWindowEx(0, WC_TABCONTROL, L"",
			WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | WS_CLIPCHILDREN,
			0, 0, 500, 300,
			hwnd, NULL, hInst, NULL);
		
		memset(&tie, 0, sizeof(TCITEM));
		tie.mask = TCIF_TEXT | TCIF_IMAGE;
		tie.iImage = -1;
		tie.pszText = L"Tab 1";
		TabCtrl_InsertItem(hwndTab, 0, &tie);
		
		memset(&tie, 0, sizeof(TCITEM));
		tie.mask = TCIF_TEXT | TCIF_IMAGE;
		tie.iImage = -1;
		tie.pszText = L"Tab 2";
		TabCtrl_InsertItem(hwndTab, 1, &tie);

		memset(&tie, 0, sizeof(TCITEM));
		tie.mask = TCIF_TEXT | TCIF_IMAGE;
		tie.iImage = -1;
		tie.pszText = L"Tab 3";
		TabCtrl_InsertItem(hwndTab, 2, &tie);

	   /*
		*
		*  Tab 1
		*
		*/

		wcex1.cbClsExtra = 0;
		wcex1.cbWndExtra = 0;
		wcex1.hInstance = hInst;
		wcex1.lpszClassName = TAB_CLASS_NAME;
		wcex1.style = CS_VREDRAW | CS_HREDRAW;
		//wcex1.cbSize = sizeof(WNDCLASSEX);
		wcex1.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex1.hIcon = NULL;
		//wcex1.hIconSm = NULL;
		wcex1.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(145, 167, 255));
		wcex1.lpszMenuName = NULL;
		wcex1.lpfnWndProc = (WNDPROC)Tab1Proc;

		if ((RegisterClass(&wcex1)) == 0) {
			MessageBox(NULL, L"Faild to register window of Tab 1", L"Error!", MB_OK);
			return 0;
		}

		GetClientRect(hwndTab, &rcRect);
		top_x = rcRect.left;
		top_y = rcRect.top + 24;
		child_width = rcRect.right - rcRect.left;
		child_height = rcRect.bottom - top_y;
		 
		hTab1Wnd = CreateWindow(
			//0,                              // Optional window styles.
			TAB_CLASS_NAME,                     // Window class
			NULL,    // Window text
			//WS_OVERLAPPEDWINDOW,             // Window style
			WS_CHILD|WS_VISIBLE,

											// Size and position
			top_x, top_y, child_width, child_height,
			//0,40,200,200,

			hwndTab,       // Parent window    
			NULL,       // Menu
			hInst,  // Instance handle
			NULL        // Additional application data
			);

		if (hTab1Wnd == NULL)
		{
			MessageBox(NULL, L"Faild to Create window of Tab 1", L"Error!", MB_OK);
			return 0;
		}

	   /*
		*
		*  Tab 2
		*
		*/

		wcex1.cbClsExtra = 0;
		wcex1.cbWndExtra = 0;
		wcex1.hInstance = hInst;
		wcex1.lpszClassName = TAB2_CLASS_NAME;
		wcex1.style = CS_VREDRAW | CS_HREDRAW;
		//wcex1.cbSize = sizeof(WNDCLASSEX);
		wcex1.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex1.hIcon = NULL;
		//wcex1.hIconSm = NULL;
		wcex1.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 10, 10));
		wcex1.lpszMenuName = NULL;
		wcex1.lpfnWndProc = (WNDPROC)Tab2Proc;

		if ((RegisterClass(&wcex1)) == 0) {
			MessageBox(NULL, L"Faild to register window of Tab 2", L"Error!", MB_OK);
			return 0;
		}


		//GetClientRect(hwndTab, &rcRect);
		//top_x = rcRect.left;
		//top_y = rcRect.top + 40;
		//child_width = rcRect.right - rcRect.left;
		//child_height = rcRect.bottom - top_y;


		hTab2Wnd = CreateWindow(
			TAB2_CLASS_NAME,                     // Window class
			NULL,    // Window text
			WS_CHILD | WS_VISIBLE,
			top_x, top_y, child_width, child_height,
			hwndTab,       // Parent window    
			NULL,       // Menu
			hInst,  // Instance handle
			NULL        // Additional application data
			);

		if (hTab2Wnd == NULL)
		{
			MessageBox(NULL, L"Faild to Create window of Tab 2", L"Error!", MB_OK);
			return 0;
		}

		/*
		*
		*  Tab 3
		*
		*/

		wcex1.cbClsExtra = 0;
		wcex1.cbWndExtra = 0;
		wcex1.hInstance = hInst;
		wcex1.lpszClassName = TAB3_CLASS_NAME;
		wcex1.style = CS_VREDRAW | CS_HREDRAW;
		//wcex1.cbSize = sizeof(WNDCLASSEX);
		wcex1.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex1.hIcon = NULL;
		//wcex1.hIconSm = NULL;
		wcex1.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(50, 200, 50));
		wcex1.lpszMenuName = NULL;
		wcex1.lpfnWndProc = (WNDPROC)Tab3Proc;

		if ((RegisterClass(&wcex1)) == 0) {
			MessageBox(NULL, L"Faild to register window of Tab 3", L"Error!", MB_OK);
			return 0;
		}

		GetClientRect(hwndTab, &rcRect);
		top_x = rcRect.left;
		top_y = rcRect.top + 24;
		child_width = rcRect.right - rcRect.left;
		child_height = rcRect.bottom - top_y;

		hTab3Wnd = CreateWindow(
			//0,                              // Optional window styles.
			TAB3_CLASS_NAME,                     // Window class
			NULL,    // Window text
					 //WS_OVERLAPPEDWINDOW,             // Window style
			WS_CHILD | WS_VISIBLE,

			// Size and position
			top_x, top_y, child_width, child_height,
			//0,40,200,200,

			hwndTab,       // Parent window    
			NULL,       // Menu
			hInst,  // Instance handle
			NULL        // Additional application data
			);

		if (hTab3Wnd == NULL)
		{
			MessageBox(NULL, L"Faild to Create window of Tab 3", L"Error!", MB_OK);
			return 0;
		}

		//ShowWindow(hTab1Wnd, SW_HIDE);
		//ShowWindow(hTab2Wnd, SW_SHOW);
		
		ShowWindow(hTab1Wnd, SW_SHOW);
		ShowWindow(hTab2Wnd, SW_HIDE);
		ShowWindow(hTab3Wnd, SW_HIDE);
		UpdateWindow(hwndTab);
	}
	return 0;

	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
			case TCN_SELCHANGING:
			{
				//MessageBox(hWnd, L"Content", L"Title", MB_OK);  // 先出现 mbox，再变换 tab
				// Return FALSE to allow the selection to change.
				return FALSE;
			}

			case TCN_SELCHANGE:
			{
				switch (TabCtrl_GetCurSel(hwndTab)) {
				case 0:
					//MessageBox(hwndTab, L"This is Tab A", L"A", MB_OK);
					ShowWindow(hTab1Wnd, SW_SHOW);
					ShowWindow(hTab2Wnd, SW_HIDE);
					ShowWindow(hTab3Wnd, SW_HIDE);
					//UpdateWindow(hwndTab);
					return 0;
					break;
					//return FALSE;
				case 1:
					//MessageBox(hwndTab, L"This is Tab B", L"B", MB_OK);
					ShowWindow(hTab1Wnd, SW_HIDE);
					ShowWindow(hTab2Wnd, SW_SHOW);
					ShowWindow(hTab3Wnd, SW_HIDE);
					//UpdateWindow(hwndTab);
					return 0;
					break;
					//return FALSE;
				case 2:
					//MessageBox(hwndTab, L"This is Tab C", L"C", MB_OK);
					ShowWindow(hTab1Wnd, SW_HIDE);
					ShowWindow(hTab2Wnd, SW_HIDE);
					ShowWindow(hTab3Wnd, SW_SHOW);
					//UpdateWindow(hwndTab);
					return 0;
					break;
					
				}
				break;
			}

		}
	}
	return 0;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		//FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK Tab1Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hIns;
	static HWND hButton1;
	static HWND hButton2;
	static HWND hwndEdit;
	NMHDR* nhd;

	TCHAR lpszLatin[] = L"Lorem ipsum dolor sit amet, consectetur \r\n"
		L"adipisicing elit, sed do eiusmod tempor \r\n"
		L"incididunt ut labore et dolore magna "
		L"aliqua. Ut enim ad minim veniam, quis "
		L"nostrud exercitation ullamco laboris nisi "
		L"ut aliquip ex ea commodo consequat. Duis "
		L"aute irure dolor in reprehenderit in "
		L"voluptate velit esse cillum dolore eu "
		L"fugiat nulla pariatur. Excepteur sint "
		L"occaecat cupidatat non proident, sunt "
		L"in culpa qui officia deserunt mollit "
		L"anim id est laborum.";

	switch (uMsg)
	{
	case WM_CREATE:
		hIns = GetModuleHandle(NULL);

		hwndEdit = CreateWindowEx(
			WS_EX_CLIENTEDGE | WS_EX_ACCEPTFILES,
			L"EDIT",   // predefined class 
			NULL,         // no window title 
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | // WS_BORDER |
			ES_READONLY | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
			5, 5, 250, 220,   // set size in WM_SIZE message 
			hwnd,         // parent window 
			(HMENU)ID_EDITCHILD,   // edit control ID 
			(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			NULL);

		hButton1 = CreateWindowEx(0, L"BUTTON", L"Press 1!",
			WS_VISIBLE | WS_CHILD | ES_LEFT,
			270, 10, 80, 30,
			hwnd,
			(HMENU)IDC_BUTTON1, hIns, NULL);

		hButton2 = CreateWindowEx(0, L"BUTTON", L"Press 2!",
			WS_VISIBLE | WS_CHILD | ES_LEFT,
			270, 50, 80, 30,
			hwnd,
			(HMENU)IDC_BUTTON2, hIns, NULL);


		/*
		HWND CreateWindowExW(
		[in]           DWORD     dwExStyle,
		[in, optional] LPCWSTR   lpClassName,
		[in, optional] LPCWSTR   lpWindowName,
		[in]           DWORD     dwStyle,
		[in]           int       X,
		[in]           int       Y,
		[in]           int       nWidth,
		[in]           int       nHeight,
		[in, optional] HWND      hWndParent,
		[in, optional] HMENU     hMenu,
		[in, optional] HINSTANCE hInstance,
		[in, optional] LPVOID    lpParam
		);
		*/
		return 0;
	case WM_COMMAND:
	//	nhd = (NMHDR*)malloc(sizeof(NMHDR));
	//	nhd->code = 123;
	//	nhd->hwndFrom = hwnd;
	//	SendMessage(GetParent(GetParent(hwnd)), WM_NOTIFY, (WPARAM)0, (LPARAM)nhd);
	//	free(nhd);
		switch (LOWORD(wParam)) {
			case IDC_BUTTON1:
			{
				SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)lpszLatin);
				/*
				LRESULT SendMessage(
				[in] HWND   hWnd,
				[in] UINT   Msg,
				[in] WPARAM wParam,
				[in] LPARAM lParam
				);
				*/
			}
			break;

			case IDC_BUTTON2:
			{

			}
			break;
					
		}
		return 0;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		//FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Tab2Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hIns;

	switch (uMsg)
	{
	case WM_COMMAND:
	{

	}
	return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		//FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Tab3Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		//FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}