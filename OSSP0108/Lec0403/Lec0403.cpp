// Lec0403.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Lec0403.h"
#define MAX_LOADSTRING 100 


#define SCALE 1 

#define TRANSLATE 2 

#define ROTATE  3 

#define SHEAR  4 

#define REFLECT  5 

#define NORMAL  6 


// Глобальні змінні 

HINSTANCE hInst;

TCHAR szTitle[MAX_LOADSTRING];

TCHAR szWindowClass[MAX_LOADSTRING];

HDC memDC;

HBITMAP hBit, hBmpImage;

int maxX, maxY;

int iTransform;


ATOM    MyRegisterClass(HINSTANCE hInstance);

BOOL    InitInstance(HINSTANCE, int);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain(HINSTANCE hInstance,

	HINSTANCE hPrevInstance,

	LPTSTR    lpCmdLine,

	int       nCmdShow)

{

	UNREFERENCED_PARAMETER(hPrevInstance);

	UNREFERENCED_PARAMETER(lpCmdLine);


	// TODO: Сюди код 

	MSG msg;

	HACCEL hAccelTable;


	// Ініціалізація глобальних змінних-рядків 

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

	LoadString(hInstance, IDC_LEC0403, szWindowClass, MAX_LOADSTRING);

	MyRegisterClass(hInstance);


	// Підтвердження ініціалізації застосунку: 

	if (!InitInstance(hInstance, nCmdShow))

	{

		return FALSE;

	}


	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LEC0403));


	while (GetMessage(&msg, NULL, 0, 0))

	{

		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))

		{

			TranslateMessage(&msg);

			DispatchMessage(&msg);

		}

	}


	return (int)msg.wParam;

}


// 

//  FUNCTION: MyRegisterClass() 

// 

//  PURPOSE: Registers the window class. 

// 

//  COMMENTS: 

// 

//    This function and its usage are only necessary if you want this code 

//    to be compatible with Win32 systems prior to the 'RegisterClassEx' 

//    function that was added to Windows 95. It is important to call this function 

//    so that the application will get 'well formed' small icons associated 

//    with it. 

// 

ATOM MyRegisterClass(HINSTANCE hInstance)

{

	WNDCLASSEX wcex;


	wcex.cbSize = sizeof(WNDCLASSEX);


	wcex.style = CS_HREDRAW | CS_VREDRAW;

	wcex.lpfnWndProc = WndProc;

	wcex.cbClsExtra = 0;

	wcex.cbWndExtra = 0;

	wcex.hInstance = hInstance;

	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LEC0403));

	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);

	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_LEC0403);

	wcex.lpszClassName = szWindowClass;

	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));


	return RegisterClassEx(&wcex);

}


// 

//   FUNCTION: InitInstance(HINSTANCE, int) 

// 

//   PURPOSE: Saves instance handle and creates main window 

// 

//   COMMENTS: 

// 

//   In this function, we save the instance handle in a global variable and 

//   create and display the main program window. 

// 

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)

{

	HWND hWnd;


	hInst = hInstance;

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,

		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);


	if (!hWnd)

	{

		return FALSE;

	}


	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);


	return TRUE;

}


// 

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM) 

// 

//  PURPOSE:  Processes messages for the main window. 

// 

//  WM_COMMAND - process the application menu 

//  WM_PAINT - Paint the main window 

//  WM_DESTROY - post a quit message and return 

// 

// 

void DrawImg(HDC hdc) {

	HPEN  gpen = CreatePen(PS_SOLID, 4, RGB(79, 197, 85));

	SelectObject(hdc, gpen);

	Ellipse(hdc, 100, 100, 400, 400);
	Ellipse(hdc, 150, 175, 200, 225);
	Ellipse(hdc, 300, 175, 350, 225);
	
	MoveToEx(hdc, 250, 200, NULL);
	LineTo(hdc, 275, 250);
	LineTo(hdc, 225, 250);
	LineTo(hdc, 250, 200);

	MoveToEx(hdc, 200, 300, NULL);
	LineTo(hdc, 300, 300);
	LineTo(hdc, 250, 350);
	LineTo(hdc, 200, 300);


	MoveToEx(hdc, 225, 100, NULL);
	LineTo(hdc, 200, 160);

	MoveToEx(hdc, 240, 100, NULL);
	LineTo(hdc, 225, 155);


	MoveToEx(hdc, 275, 100, NULL);
	LineTo(hdc, 295, 160);

	MoveToEx(hdc, 290, 105, NULL);
	LineTo(hdc, 315, 155);

	DeleteObject(gpen);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

{

	int wmId, wmEvent;

	PAINTSTRUCT ps;

	HDC hdc;

	HBRUSH hBrush;

	RECT rect;


	switch (message)

	{

	case WM_CREATE:

		maxX = GetSystemMetrics(SM_CXSCREEN);

		maxY = GetSystemMetrics(SM_CYSCREEN);

		hdc = GetDC(hWnd);

		memDC = CreateCompatibleDC(hdc);

		hBit = CreateCompatibleBitmap(hdc, maxX, maxY);

		SelectObject(memDC, hBit);

		hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);

		SelectObject(memDC, hBrush);

		PatBlt(memDC, 0, 0, maxX, maxY, PATCOPY);

		ReleaseDC(hWnd, hdc);


		// Завантаження бітмапу з ресурсу 

		hBmpImage = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));



	case WM_COMMAND:

		wmId = LOWORD(wParam);

		wmEvent = HIWORD(wParam);

		// Меню: 

		switch (wmId)

		{

		case IDM_ABOUT:

			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);

			break;

		case IDM_EXIT:

			DestroyWindow(hWnd);

			break;

		case ID_IMAGE_IMAGESSHOW:

			SelectObject(memDC, hBmpImage);

			InvalidateRect(hWnd, NULL, 1);

			break;

		case ID_IMAGE_SCALE:

			iTransform = SCALE;

			InvalidateRect(hWnd, NULL, 1);

			break;

		case ID_IMAGE_TRANSLATE:

			iTransform = TRANSLATE;

			InvalidateRect(hWnd, NULL, 1);

			break;

		case ID_IMAGE_ROTATE:

			iTransform = ROTATE;

			InvalidateRect(hWnd, NULL, 1);

			break;

		case ID_IMAGE_SHEAR:

			iTransform = SHEAR;

			InvalidateRect(hWnd, NULL, 1);

			break;

		case ID_IMAGE_REFLECT:

			iTransform = REFLECT;

			InvalidateRect(hWnd, NULL, 1);

			break;

		case ID_IMAGE_NORMAL:

			iTransform = NORMAL;

			InvalidateRect(hWnd, NULL, 1);

			break;

		default:

			return DefWindowProc(hWnd, message, wParam, lParam);

		}

		break;

	case WM_PAINT:

		
		hdc = BeginPaint(hWnd, &ps);


		

		SetGraphicsMode(hdc, GM_ADVANCED);



		XFORM xForm;

		switch (iTransform)

		{

		case SCALE:    // Зменшуємо у два рази зображення 

			xForm.eM11 = (FLOAT) 0.5;

			xForm.eM12 = (FLOAT) 0.0;

			xForm.eM21 = (FLOAT) 0.0;

			xForm.eM22 = (FLOAT) 0.5;

			xForm.eDx = (FLOAT) 0.0;

			xForm.eDy = (FLOAT) 0.0;

			SetWorldTransform(hdc, &xForm);

			break;

		case TRANSLATE:   // Завдання 2

			xForm.eM11 = (FLOAT)1.0;

			xForm.eM12 = (FLOAT) 0.0;

			xForm.eM21 = (FLOAT) 0.0;

			xForm.eM22 = (FLOAT) 1.0;

			xForm.eDx = (FLOAT) -301.6;

			xForm.eDy = (FLOAT) -315.0;

			SetWorldTransform(hdc, &xForm);

			break;

		case ROTATE: // Поворот на 45 градусів проти часової стрілки 

			xForm.eM11 = (FLOAT) 0.7071; //0.7071

			xForm.eM12 = (FLOAT) 0.7071;//0.7071

			xForm.eM21 = (FLOAT)-0.7071;

			xForm.eM22 = (FLOAT) 0.7071;

			xForm.eDx = (FLOAT) 500.0;

			xForm.eDy = (FLOAT) 0.0;

			SetWorldTransform(hdc, &xForm);

			break;

		case SHEAR:       // Викривлення зображення 

			xForm.eM11 = (FLOAT) 0.5;

			xForm.eM12 = (FLOAT) 1.1;

			xForm.eM21 = (FLOAT) 2.1;

			xForm.eM22 = (FLOAT) 1.6;

			xForm.eDx = (FLOAT) 0.0;

			xForm.eDy = (FLOAT) 0.0;

			SetWorldTransform(hdc, &xForm);

			break;

		case REFLECT:     // Дзеркальне відображення по горизонтальній осі 

			xForm.eM11 = (FLOAT)-1.0;

			xForm.eM12 = (FLOAT) 0.0;

			xForm.eM21 = (FLOAT) 0.0;

			xForm.eM22 = (FLOAT) 1.0;

			xForm.eDx = (FLOAT) 730.0;

			xForm.eDy = (FLOAT) 0.0;

			SetWorldTransform(hdc, &xForm);

			break;

		case NORMAL:      // Встановлюємо значення перетворення 

			xForm.eM11 = (FLOAT) 1.0;

			xForm.eM12 = (FLOAT) 0.0;

			xForm.eM21 = (FLOAT) 0.0;

			xForm.eM22 = (FLOAT) 1.0;

			xForm.eDx = (FLOAT) 0.0;

			xForm.eDy = (FLOAT) 0.0;

			SetWorldTransform(hdc, &xForm);

			break;

		}

		// Copy the bits from the memory DC into the current dc 

		GetClientRect(hWnd, (LPRECT)&rect);

		DPtoLP(hdc, (LPPOINT)&rect, 2);


		BitBlt(hdc, 719, 310, 719, 723, memDC, 0, 0, SRCCOPY);

		DrawImg(hdc);

		EndPaint(hWnd, &ps);

		break;

	case WM_DESTROY:

		DeleteDC(memDC);


		DeleteObject(hBmpImage);

		PostQuitMessage(0);

		break;

	default:

		return DefWindowProc(hWnd, message, wParam, lParam);

	}

	return 0;

}

// Message handler for about box. 

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
