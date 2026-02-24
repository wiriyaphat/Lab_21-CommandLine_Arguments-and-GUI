#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

HWND hEditlek_1, hEditLek_2, hResult, hMainWindow;
HMENU hMenu;
void addMenus(HWND);
void addControls(HWND);

#define Help_Destroys 1
#define Plus 2
#define Minus 3
#define Koon 4
#define Harn 5


/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
//--------------------------------------------------------------------------
		case WM_CREATE: {
			
			addMenus(hwnd);
			addControls(hwnd);
			break;
		}
//--------------------------------------------------------------------------
		case WM_COMMAND: {

				char num1[10], num2[10], result_eyes[50];
				double a, b, result;
				GetWindowText(hEditlek_1, num1, 10);
				GetWindowText(hEditLek_2, num2, 10);
				a = atof(num1);
				b = atof(num2);
				


			switch(wParam)
			{
				case Help_Destroys:
					MessageBeep(MB_OK);
					DestroyWindow(hwnd);
					break;

				case Plus:
					result = a + b;
					sprintf(result_eyes, "%.2f", result);
					MessageBox(hwnd,result_eyes,"Result",MB_OK);
					break;

				case Minus:
					result = a - b;
					sprintf(result_eyes, "%.2f", result);
					MessageBox(hwnd,result_eyes,"Result",MB_OK);
					break;

				case Koon:
					result = a*b;
					sprintf(result_eyes, "%.2f", result);
					MessageBox(hwnd,result_eyes,"Result",MB_OK);
					break;
				
				case Harn:
					result = a/b;
					if (b == 0){
						MessageBox(hwnd,"wRoNg cAn'T dIvIdEd bY 0","Result",MB_OK);
						break;
					}
					sprintf(result_eyes, "%.2f", result);
					MessageBox(hwnd,result_eyes,"Result",MB_OK);
					break;
			}

			break;
		}
//--------------------------------------------------------------------------
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(178,34,34));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	//-----------------------------------------------------------------
	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}



	hMainWindow = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPED| WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200	, /* height */
		NULL,NULL,hInstance,NULL);

	if(hMainWindow == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
//--------------------------------------------------------------------------
void addMenus(HWND hWnd){
	hMenu = CreateMenu();
	AppendMenu(hMenu,MF_STRING, Help_Destroys, "Help");
	SetMenu(hWnd, hMenu);
}
//--------------------------------------------------------------------------
void addControls(HWND hWnd){
	CreateWindowW(L"Static", L"Please input 2 numbers.", WS_VISIBLE | WS_CHILD , 35,0,180,30,hWnd,NULL,NULL,NULL);

	hEditlek_1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE , 35,50,50,30,hWnd,NULL,NULL,NULL);
	hEditLek_2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE , 165,50,50,30,hWnd,NULL,NULL,NULL);
	CreateWindowW(L"Button", L"+", WS_VISIBLE | WS_CHILD , 35,120,20,20,hWnd,(HMENU)Plus,NULL,NULL);
	CreateWindowW(L"Button", L"-", WS_VISIBLE | WS_CHILD , 65,120,20,20,hWnd,(HMENU)Minus,NULL,NULL);
	CreateWindowW(L"Button", L"*", WS_VISIBLE | WS_CHILD , 165,120,20,20,hWnd,(HMENU)Koon,NULL,NULL);
	CreateWindowW(L"Button", L"/", WS_VISIBLE | WS_CHILD , 195,120,20,20,hWnd,(HMENU)Harn,NULL,NULL);

	
}





