#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <stdarg.h>
#include"resource.h"

int CDECL myMessageBox(TCHAR * szCaption, size_t iStyle, TCHAR * szFormat, ...);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void generate_integerTocip(int symbolNumber, char *topic);
void generate_fractionTocip(int symbolNumber, char *topic);
void generate_factorialTocip(char *topic);
void clearScreen(HWND hwnd, HWND hwndInput1, HWND hwndInput2, HWND hwndInput3, HWND btnHwnd1, HWND btnHwnd2, HWND btnHwnd3, HWND btnHwnd4, HWND btnHwnd5, HWND btnHwnd6);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	TCHAR szAppName[] = TEXT("CreateChildWindow");

	HWND        hwnd;
	MSG            msg;
	WNDCLASS    wndclass;
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.hInstance = hInstance;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("无法注册窗口类!"), szAppName, MB_OK | MB_ICONERROR);
		return 0;
	}

	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	hwnd = CreateWindow(szAppName, TEXT("四则运算"),
		WS_CAPTION,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL, hMenu, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HMENU hMenu;
	
	static HWND hwndInput1,hwndInput2,hwndInput3;
	static HWND btnHwnd1, btnHwnd2, btnHwnd3, btnHwnd4, btnHwnd5, btnHwnd6;
	char Buffer[100];
	static int topicNumber, symbolNumber, i, ILength;
	float answer, userAnswer=0;
	char topic[100] = {'\0'};
	char burff[] = "#";
	static int bgcolor = 1;

	HBRUSH hbmp1 = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	HBRUSH hbmp2 = (HBRUSH)GetStockObject(GRAY_BRUSH);
	HBRUSH hbmp3 = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	HBRUSH hbmp4 = (HBRUSH)GetStockObject(BLACK_BRUSH);
	HBRUSH hbmp5 = (HBRUSH)GetStockObject(WHITE_BRUSH);

	switch (message)
	{
	case WM_COMMAND:
		hMenu = GetMenu(hwnd);

		switch (LOWORD(wParam))
		{
		case IDM_Integer:
			clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2, btnHwnd3, btnHwnd4, btnHwnd5, btnHwnd6);
			hdc = GetDC(hwnd);
			TextOut(hdc, 300, 150, "题目类型:       整数", 20);
			TextOut(hdc, 300, 180, "题目   数量:", 12);
			TextOut(hdc, 300, 210, "运算符数量:", 11);

			hwndInput1 = CreateWindow(TEXT("edit"), NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER |
				ES_LEFT | ES_NUMBER,
				400, 180, 25, 22,
				hwnd, (HMENU)1, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
			hwndInput2 = CreateWindow(TEXT("edit"), NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER |
				ES_LEFT | ES_NUMBER,
				400, 210, 25, 22,
				hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
			btnHwnd1 = CreateWindow(TEXT("button"), TEXT("确认"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				310, 250,
				100, 30,
				hwnd,
				(HMENU)1,
				(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
				NULL);
			break;
		case 1:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetWindowText(hwndInput1, Buffer, 100);
				topicNumber = atoi(Buffer);
				GetWindowText(hwndInput2, Buffer, 100);
				symbolNumber = atoi(Buffer);
				i = topicNumber;
				if ((topicNumber <= 5 && topicNumber != 0) && (symbolNumber >= 2 && symbolNumber <= 4))
				{
					clearScreen( hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2, btnHwnd3,btnHwnd4,btnHwnd5, btnHwnd6);
					hdc = GetDC(hwnd);
					generate_integerTocip(symbolNumber, topic);
					
					ILength = lstrlen(topic);
					TextOut(hdc, 300, 120, "题目类型:       整数", 20);
					TextOut(hdc, 300, 150, topic, ILength);
					TextOut(hdc, 300, 210, "答案      :", 11);
                    lstrcat(topic, burff);
					hwndInput3 = CreateWindow(TEXT("edit"), NULL,
						WS_CHILD | WS_VISIBLE | WS_BORDER |
						ES_LEFT,
						380, 210, 100, 22,
						hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
					btnHwnd2 = CreateWindow(TEXT("button"), TEXT("确认"),
						WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						350, 250,
						100, 30,
						hwnd,
						(HMENU)2,
						(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
						NULL);
				}
				else {
					MessageBox(hwnd, TEXT("您输入的数据有误，请重新输入！"), TEXT("提示"), MB_OK);
				}
				break;
			}
			break;
		case 2:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetWindowText(hwndInput3, Buffer, 100);
				answer = atoi(Buffer);
				MessageBox(hwnd, TEXT("很抱歉功能未实现"), TEXT("提示"), MB_OK);
				if (answer == userAnswer)
				{
					
				}
				else
				{
					 
				}
				i--;
				if (i > 0)
				{
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2, btnHwnd3, btnHwnd4, btnHwnd5, btnHwnd6);
					hdc = GetDC(hwnd);
					generate_integerTocip(symbolNumber, topic);
					ILength = lstrlen(topic);
					TextOut(hdc, 300, 120, "题目类型:       整数", 20);
					TextOut(hdc, 300, 150, topic, ILength);
					TextOut(hdc, 300, 210, "答案      :", 11);

					hwndInput3 = CreateWindow(TEXT("edit"), NULL,
						WS_CHILD | WS_VISIBLE | WS_BORDER |
						ES_LEFT,
						380, 210, 100, 22,
						hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
					btnHwnd2 = CreateWindow(TEXT("button"), TEXT("确认"),
						WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						350, 250,
						100, 30,
						hwnd,
						(HMENU)2,
						(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
						NULL);
				}
				else {
					MessageBox(hwnd, TEXT("回答完毕！"), TEXT(""), MB_OK);
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2, btnHwnd3, btnHwnd4, btnHwnd5, btnHwnd6);
				}
				break;
			}
			break;

			case IDM_Fraction:
				clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2, btnHwnd3, btnHwnd4, btnHwnd5, btnHwnd6);
				hdc = GetDC(hwnd);
				TextOut(hdc, 300, 150, "题目类型:       分数", 20);
				TextOut(hdc, 300, 180, "题目   数量:", 12);
				TextOut(hdc, 300, 210, "运算符数量:", 11);
				hwndInput1 = CreateWindow(TEXT("edit"), NULL,
					WS_CHILD | WS_VISIBLE | WS_BORDER |
					ES_LEFT | ES_NUMBER,
					400, 180, 25, 22,
					hwnd, (HMENU)1, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
				hwndInput2 = CreateWindow(TEXT("edit"), NULL,
					WS_CHILD | WS_VISIBLE | WS_BORDER |
					ES_LEFT | ES_NUMBER,
					400, 210, 25, 22,
					hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
				btnHwnd3 = CreateWindow(TEXT("button"), TEXT("确认"),
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					310, 250,
					100, 30,
					hwnd,
					(HMENU)3,
					(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
					NULL);
				break;
			case 3:
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
					GetWindowText(hwndInput1, Buffer, 100);
					topicNumber = atoi(Buffer);
					GetWindowText(hwndInput2, Buffer, 100);
					symbolNumber = atoi(Buffer);
					i = topicNumber;
					if ((topicNumber <= 5 && topicNumber != 0) && (symbolNumber >= 2 && symbolNumber <= 4))
					{
						clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2, btnHwnd3, btnHwnd4, btnHwnd5, btnHwnd6);
						hdc = GetDC(hwnd);
						generate_fractionTocip(symbolNumber, topic);
						ILength = lstrlen(topic);
						TextOut(hdc, 300, 120, "题目类型:       分数", 20);
						TextOut(hdc, 300, 150, topic, ILength);
						TextOut(hdc, 300, 210, "答案      :", 11);

						hwndInput3 = CreateWindow(TEXT("edit"), NULL,
							WS_CHILD | WS_VISIBLE | WS_BORDER |
							ES_LEFT,
							380, 210, 100, 22,
							hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
						btnHwnd4 = CreateWindow(TEXT("button"), TEXT("确认"),
							WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
							350, 250,
							100, 30,
							hwnd,
							(HMENU)4,
							(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
							NULL);
					}
					else {
						MessageBox(hwnd, TEXT("您输入的数据有误，请重新输入！"), TEXT(""), MB_OK);
					}
					break;
				}
				break;
			case 4:
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
					GetWindowText(hwndInput3, Buffer, 100);
					answer = atoi(Buffer);
					MessageBox(hwnd, TEXT("很抱歉功能未实现"), TEXT("提示"), MB_OK);
					i--;
					if (i > 0)
					{
						clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2, btnHwnd3, btnHwnd4, btnHwnd5, btnHwnd6);
						hdc = GetDC(hwnd);
						generate_fractionTocip(symbolNumber, topic);
						ILength = lstrlen(topic);
						TextOut(hdc, 300, 120, "题目类型:       分数", 20);
						TextOut(hdc, 300, 150, topic, ILength);
						TextOut(hdc, 300, 210, "答案      :", 11);

						hwndInput3 = CreateWindow(TEXT("edit"), NULL,
							WS_CHILD | WS_VISIBLE | WS_BORDER |
							ES_LEFT,
							380, 210, 100, 22,
							hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
						btnHwnd2 = CreateWindow(TEXT("button"), TEXT("确认"),
							WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
							350, 250,
							100, 30,
							hwnd,
							(HMENU)4,
							(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
							NULL);
					}
					else {
						MessageBox(hwnd, TEXT("回答完毕！"), TEXT(""), MB_OK);
						clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2, btnHwnd3, btnHwnd4, btnHwnd5, btnHwnd6);
					}
					break;
				}
				break;

			case IDM_Factorial:
				clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2, btnHwnd3, btnHwnd4, btnHwnd5, btnHwnd6);
				hdc = GetDC(hwnd);
				TextOut(hdc, 300, 150, "题目类型:       阶乘", 20);
				TextOut(hdc, 300, 180, "题目   数量:", 12);
				hwndInput1 = CreateWindow(TEXT("edit"), NULL,
					WS_CHILD | WS_VISIBLE | WS_BORDER |
					ES_LEFT | ES_NUMBER,
					400, 180, 25, 22,
					hwnd, (HMENU)5, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
				btnHwnd5 = CreateWindow(TEXT("button"), TEXT("确认"),
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					310, 250,
					100, 30,
					hwnd,
					(HMENU)5,
					(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
					NULL);
				break;
			case 5:
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
					GetWindowText(hwndInput1, Buffer, 100);
					topicNumber = atoi(Buffer);
					i = topicNumber;
					if (topicNumber <= 5 && topicNumber != 0)
					{
						clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2, btnHwnd3, btnHwnd4, btnHwnd5, btnHwnd6);
						hdc = GetDC(hwnd);
						generate_factorialTocip(topic);
						ILength = lstrlen(topic);
						TextOut(hdc, 300, 120, "题目类型:       阶乘", 20);
						TextOut(hdc, 300, 150, topic, ILength);
						TextOut(hdc, 300, 210, "答案      :", 11);

						hwndInput2 = CreateWindow(TEXT("edit"), NULL,
							WS_CHILD | WS_VISIBLE | WS_BORDER |
							ES_LEFT,
							380, 210, 100, 22,
							hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
						btnHwnd6 = CreateWindow(TEXT("button"), TEXT("确认"),
							WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
							350, 250,
							100, 30,
							hwnd,
							(HMENU)6,
							(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
							NULL);
					}
					else {
						MessageBox(hwnd, TEXT("您输入的数据有误，请重新输入！"), TEXT(""), MB_OK);
					}
					break;
				}
				break;
			case 6:
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
					GetWindowText(hwndInput2, Buffer, 100);
					answer = atoi(Buffer); 
					MessageBox(hwnd, TEXT("很抱歉功能未实现"), TEXT("提示"), MB_OK);
					i--;
					if (i>0)
					{
						clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2, btnHwnd3, btnHwnd4, btnHwnd5, btnHwnd6);
						hdc = GetDC(hwnd);
						generate_factorialTocip(topic);
						ILength = lstrlen(topic);
						TextOut(hdc, 300, 120, "题目类型:       阶乘", 20);
						TextOut(hdc, 300, 150, topic, ILength);
						TextOut(hdc, 300, 210, "答案      :", 11);

						hwndInput2 = CreateWindow(TEXT("edit"), NULL,
							WS_CHILD | WS_VISIBLE | WS_BORDER |
							ES_LEFT,
							380, 210, 100, 22,
							hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
						btnHwnd6 = CreateWindow(TEXT("button"), TEXT("确认"),
							WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
							350, 250,
							100, 30,
							hwnd,
							(HMENU)6,
							(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
							NULL);
					}
					else {
						MessageBox(hwnd, TEXT("回答完毕！"), TEXT(""), MB_OK);
						clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2, btnHwnd3, btnHwnd4, btnHwnd5, btnHwnd6);
					}
					break;
				}
				break;

		case IDM_Background:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2, btnHwnd3, btnHwnd4, btnHwnd5, btnHwnd6);
				if (bgcolor == 1) {
					SetClassLongPtr(hwnd, GCL_HBRBACKGROUND, (long)hbmp1);
					InvalidateRect(hwnd, NULL, TRUE);
					UpdateWindow(hwnd);
					bgcolor = 2;
					break;
				}
				else if (bgcolor == 2) {
					SetClassLongPtr(hwnd, GCL_HBRBACKGROUND, (long)hbmp2);
					InvalidateRect(hwnd, NULL, TRUE);
					UpdateWindow(hwnd);
					bgcolor = 3;
					break;
				}
				else if (bgcolor == 3) {
					SetClassLongPtr(hwnd, GCL_HBRBACKGROUND, (long)hbmp3);
					InvalidateRect(hwnd, NULL, TRUE);
					UpdateWindow(hwnd);
					bgcolor = 4;
					break;
				}
				else if (bgcolor == 4) {
					SetClassLongPtr(hwnd, GCL_HBRBACKGROUND, (long)hbmp4);
					InvalidateRect(hwnd, NULL, TRUE);
					UpdateWindow(hwnd);
					bgcolor = 5;
					break;
				}
				else if (bgcolor == 5) {
					SetClassLongPtr(hwnd, GCL_HBRBACKGROUND, (long)hbmp5);
					InvalidateRect(hwnd, NULL, TRUE);
					UpdateWindow(hwnd);
					bgcolor = 1;
					break;
				}
			}
			break;

		case IDM_Explain:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				MessageBox(hwnd, TEXT("点击生成题目选择题型后，输入题目数量及运算符号的数量;\n题目数量不为0且最大不超过5，运算符号数目大于2而不超过4！"), TEXT("说明"), MB_OK);
				break;
			}
			break;
		case IDM_Exit:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				DestroyWindow(hwnd);
				break;
			}
			break;
		}

		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
int CDECL myMessageBox(TCHAR * szCaption, size_t iStyle, TCHAR * szFormat, ...)

{  //myMessageBox函数参数: 标题, 样式, 格式化输出内容
  //CDECL为调用规则, 在WINDEF.H定义为: #define CDECL _cdecl

	TCHAR   szBuffer[1024];
	va_list pArgs;

	va_start(pArgs, szFormat);
	snprintf(szBuffer, sizeof(szBuffer) / sizeof(TCHAR), szFormat, pArgs);
	//sizeof(szBuffer) / sizeof (TCHAR)得到最大能容下的字符个数
	va_end(pArgs);

	return MessageBox(NULL, szBuffer, szCaption, iStyle);

}
void generate_integerTocip(int symbolNumber, char *topic)
{
	char burff[200];
	int i, random, symbolRandom;
	char symbol;
	srand((unsigned)time(NULL));
	for (i = 0; i < symbolNumber; i++)
	{
		random = rand() % 100 + 1;
		symbolRandom = rand() % 4 + 1;
		snprintf(burff, 200, "%d", random);
		lstrcat(topic, burff);
		switch (symbolRandom)
		{
		case 1:
			symbol = '+';
			break;
		case 2:
			symbol = '-';
			break;
		case 3:
			symbol = '*';
			break;
		case 4:
			symbol = '/';
			break;
		}
		snprintf(burff, 200, "%c", symbol);
		lstrcat(topic, burff);
	}
	random = rand() % 100 + 1;
	snprintf(burff, 200, "%d", random);
	lstrcat(topic, burff);

}
void generate_fractionTocip(int symbolNumber, char *topic)
{
	char burff[200];
	int i, symbolRandom, random1,random2;
	char symbol;
	srand((unsigned)time(NULL));
	for (i = 0; i < symbolNumber; i++)
	{
		random1 = rand() % 100 + 1;
		random2 = rand() % 100 + 1;
		symbolRandom = rand() % 4 + 1;
		snprintf(burff, 200, "%d", random1);
		lstrcat(topic, burff);
		snprintf(burff, 200, "%c", '/');
		lstrcat(topic, burff);
		snprintf(burff, 200, "%d", random2);
		lstrcat(topic, burff);
		switch (symbolRandom)
		{
		case 1:
			symbol = '+';
			break;
		case 2:
			symbol = '-';
			break;
		case 3:
			symbol = '*';
			break;
		case 4:
			symbol = '/';
			break;
		}
		snprintf(burff, 200, "%c", symbol);
		lstrcat(topic, burff);
	}
	random1 = rand() % 100 + 1;
	random2 = rand() % 100 + 1;
	snprintf(burff, 200, "%d", random1);
	lstrcat(topic, burff);
	snprintf(burff, 200, "%c", '/');
	lstrcat(topic, burff);
	snprintf(burff, 200, "%d", random2);
	lstrcat(topic, burff);
}
void generate_factorialTocip(char *topic)
{
	char burff[200];
	int  random;
	srand((unsigned)time(NULL));
	random = rand() % 100 + 1;
	snprintf(burff, 200, "%d ! = ", random); 
	lstrcat(topic, burff);
}
void clearScreen(HWND hwnd, HWND hwndInput1, HWND hwndInput2, HWND hwndInput3, HWND btnHwnd1, HWND btnHwnd2, HWND btnHwnd3, HWND btnHwnd4, HWND btnHwnd5, HWND btnHwnd6)
{
	InvalidateRect(hwnd, NULL, TRUE);
	UpdateWindow(hwnd);
	DestroyWindow(hwndInput1);
	DestroyWindow(hwndInput2);
	DestroyWindow(hwndInput3);
	DestroyWindow(btnHwnd1);
	DestroyWindow(btnHwnd2);
	DestroyWindow(btnHwnd3);
	DestroyWindow(btnHwnd4);
	DestroyWindow(btnHwnd5);
	DestroyWindow(btnHwnd6);
}