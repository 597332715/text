#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void generate_integerTocip(int symbolNumber, char *topic);
void generate_fractionTocip(int symbolNumber, char *topic);
int generate_factorialTocip(char *topic);
int fac(int n);
void clearScreen(HWND hwnd, HWND hwndInput1, HWND hwndInput2, HWND hwndInput3, HWND btnHwnd1, HWND btnHwnd2);


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

	static HWND hwndInput1, hwndInput2, hwndInput3;
	static HWND btnHwnd1, btnHwnd2;
	char burff[200] , Buffer[100], topic[100] = { '\0' };
	static int topicNumber, symbolNumber, ILength, i;
	static float answer, userAnswer;
	static int factorial, factorialAnswer, factorialUserAnswer;
	static int bgcolor = 1;
	static clock_t start, finish;
	static int correct = 0, mistake = 0;
	double cost;

	HBRUSH hbmp1 = (HBRUSH)GetStockObject(LTGRAY_BRUSH);//背景颜色LTGRAY
	HBRUSH hbmp2 = (HBRUSH)GetStockObject(GRAY_BRUSH);//背景颜色GRAY
	HBRUSH hbmp3 = (HBRUSH)GetStockObject(DKGRAY_BRUSH);//背景颜色DKGRAY
	HBRUSH hbmp4 = (HBRUSH)GetStockObject(BLACK_BRUSH);//背景颜色BLACK
	HBRUSH hbmp5 = (HBRUSH)GetStockObject(WHITE_BRUSH);//背景颜色WHITE

	switch (message)
	{
	case WM_COMMAND:
		hMenu = GetMenu(hwnd);

		switch (LOWORD(wParam))
		{
		case IDM_Integer://整数按钮的点击事件
			clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
			hdc = GetDC(hwnd);

			TextOut(hdc, 300, 150, "题目类型:       整数", 20);
			TextOut(hdc, 300, 180, "题目   个数:", 12);
			TextOut(hdc, 300, 210, "运算符个数:", 11);

			//编辑子窗口，用于接收用户输入的题目个数
			hwndInput1 = CreateWindow(TEXT("edit"), NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER |
				ES_LEFT | ES_NUMBER,
				400, 180, 25, 22,
				hwnd, (HMENU)1, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
			//编辑子窗口，用于接收用户输入的运算符个数
			hwndInput2 = CreateWindow(TEXT("edit"), NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER |
				ES_LEFT | ES_NUMBER,
				400, 210, 25, 22,
				hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
			//按钮子窗口，用于确认用户输入题目个数与运算符个数
			btnHwnd1 = CreateWindow(TEXT("button"), TEXT("确认"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				310, 250,
				100, 30,
				hwnd,
				(HMENU)1,
				(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
				NULL);
			break;

		case 1://按钮点击事件，用于确认用户输入题目个数与运算符个数
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
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
					hdc = GetDC(hwnd);
					generate_integerTocip(symbolNumber, topic);
					ILength = lstrlen(topic);

					TextOut(hdc, 300, 120, "题目类型:       整数", 20);
					TextOut(hdc, 300, 150, topic, ILength);
					TextOut(hdc, 300, 210, "答案      :", 11);

					//编辑子窗口，用于接收用户输入的答案
					hwndInput3 = CreateWindow(TEXT("edit"), NULL,
						WS_CHILD | WS_VISIBLE | WS_BORDER |
						ES_LEFT,
						380, 210, 100, 22,
						hwnd, (HMENU)3, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
					//按钮子窗口，用于确认用户输入的答案
					btnHwnd2 = CreateWindow(TEXT("button"), TEXT("确认"),
						WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						350, 250,
						100, 30,
						hwnd,
						(HMENU)2,
						(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
						NULL);
				}
				else
				{
					MessageBox(hwnd, TEXT("您输入的数据有误，请重新输入！"), TEXT("提示"), MB_OK);
				}
				break;
			}
			break;

		case 2://按钮点击事件，用于确认用户输入的答案
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetWindowText(hwndInput3, Buffer, 100);
				answer = atof(Buffer);
				i--;
				MessageBox(hwnd, TEXT("很抱歉功能未实现"), TEXT("提示"), MB_OK);
				/*if (answer == userAnswer)
				{
					MessageBox(hwnd, TEXT("回答正确！"), TEXT("结果"), MB_OK);
				}
				else
				{
					 MessageBox(hwnd, TEXT("回答错误！"), TEXT("结果"), MB_OK);
				}*/

				//另类的出题循环方法，由于无法使用do-while循环，故用此下策
				if (i > 0)
				{
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
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
						hwnd, (HMENU)3, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

					btnHwnd2 = CreateWindow(TEXT("button"), TEXT("确认"),
						WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						350, 250,
						100, 30,
						hwnd,
						(HMENU)2,
						(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
						NULL);
				}
				else
				{
					MessageBox(hwnd, TEXT("回答完毕！"), TEXT("结果"), MB_OK);
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
				}
				break;
			}
			break;

		case IDM_Fraction://分数按钮的点击事件
			clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
			hdc = GetDC(hwnd);

			TextOut(hdc, 300, 150, "题目类型:       分数", 20);
			TextOut(hdc, 300, 180, "题目   数量:", 12);
			TextOut(hdc, 300, 210, "运算符数量:", 11);

			//编辑子窗口，用于接收用户输入的题目个数
			hwndInput1 = CreateWindow(TEXT("edit"), NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER |
				ES_LEFT | ES_NUMBER,
				400, 180, 25, 22,
				hwnd, (HMENU)1, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

			//编辑子窗口，用于接收用户输入的运算符个数
			hwndInput2 = CreateWindow(TEXT("edit"), NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER |
				ES_LEFT | ES_NUMBER,
				400, 210, 25, 22,
				hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
			//按钮子窗口，用于确认用户输入的题目个数与运算符个数
			btnHwnd1 = CreateWindow(TEXT("button"), TEXT("确认"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				310, 250,
				100, 30,
				hwnd,
				(HMENU)3,
				(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
				NULL);
			break;

		case 3://按钮点击事件，用于确认用户输入的题目数个数与运算符个数
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
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
					hdc = GetDC(hwnd);
					generate_fractionTocip(symbolNumber, topic);
					ILength = lstrlen(topic);

					TextOut(hdc, 300, 120, "题目类型:       分数", 20);
					TextOut(hdc, 300, 150, topic, ILength);
					TextOut(hdc, 300, 210, "答案      :", 11);

					//编辑子窗口，用于接收用户输入的答案
					hwndInput3 = CreateWindow(TEXT("edit"), NULL,
						WS_CHILD | WS_VISIBLE | WS_BORDER |
						ES_LEFT,
						380, 210, 100, 22,
						hwnd, (HMENU)3, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
					//按钮子窗口，用于确认用户输入的答案
					btnHwnd2 = CreateWindow(TEXT("button"), TEXT("确认"),
						WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						350, 250,
						100, 30,
						hwnd,
						(HMENU)4,
						(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
						NULL);
				}
				else
				{
					MessageBox(hwnd, TEXT("您输入的数据有误，请重新输入！"), TEXT("提示"), MB_OK);
				}
				break;
			}
			break;

		case 4://按钮点击事件，用于确认用户输入的答案
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetWindowText(hwndInput3, Buffer, 100);
				answer = atof(Buffer);
				i--;
				MessageBox(hwnd, TEXT("很抱歉功能未实现"), TEXT("提示"), MB_OK);
				/*if (answer == userAnswer)
				  {
					  MessageBox(hwnd, TEXT("回答正确！"), TEXT("结果"), MB_OK);
				  }
				  else
				  {
					  MessageBox(hwnd, TEXT("回答错误！"), TEXT("结果"), MB_OK);
				  }*/

				  //另类的出题循环方法，由于无法使用do-while循环，故用此下策
				if (i > 0)
				{
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
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
						hwnd, (HMENU)3, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

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
					MessageBox(hwnd, TEXT("回答完毕！"), TEXT("结果"), MB_OK);
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
				}
				break;
			}
			break;

		case IDM_Factorial://阶乘按钮的点击事件
			clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
			hdc = GetDC(hwnd);

			TextOut(hdc, 300, 150, "题目类型:       阶乘", 20);
			TextOut(hdc, 300, 180, "题目   数量:", 12);

			//编辑子窗口，用于接收用户输入的题目个数
			hwndInput1 = CreateWindow(TEXT("edit"), NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER |
				ES_LEFT | ES_NUMBER,
				400, 180, 25, 22,
				hwnd, (HMENU)1, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
			//按钮子窗口，用于确认用户输入的题目个数
			btnHwnd1 = CreateWindow(TEXT("button"), TEXT("确认"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				310, 250,
				100, 30,
				hwnd,
				(HMENU)5,
				(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
				NULL);
			break;

		case 5://按钮点击事件，用于确认用户输入的题目个数
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetWindowText(hwndInput1, Buffer, 100);
				topicNumber = atoi(Buffer);
				i = topicNumber;

				if (topicNumber <= 5 && topicNumber != 0)
				{
					start = clock();
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
					hdc = GetDC(hwnd);
					factorial = generate_factorialTocip(topic);
					ILength = lstrlen(topic);
					factorialAnswer = fac(factorial);

					TextOut(hdc, 300, 120, "题目类型:       阶乘", 20);
					TextOut(hdc, 300, 150, topic, ILength);
					TextOut(hdc, 300, 210, "答案      :", 11);

					//编辑子窗口，用于接收用户输入的答案
					hwndInput2 = CreateWindow(TEXT("edit"), NULL,
						WS_CHILD | WS_VISIBLE | WS_BORDER |
						ES_LEFT,
						380, 210, 100, 22,
						hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
					//按钮子窗口，用于确认用户输入的答案
					btnHwnd2 = CreateWindow(TEXT("button"), TEXT("确认"),
						WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						350, 250,
						100, 30,
						hwnd,
						(HMENU)6,
						(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
						NULL);
				}
				else
				{
					MessageBox(hwnd, TEXT("您输入的数据有误，请重新输入！"), TEXT("提示"), MB_OK);
				}
				break;
			}
			break;

		case 6://按钮点击事件，用于确认用户输入的答案
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetWindowText(hwndInput2, Buffer, 100);
				factorialUserAnswer = atoi(Buffer);
				i--;

				//判断答案正误
				if (factorialAnswer == factorialUserAnswer)
				{
					correct++;
					MessageBox(hwnd, TEXT("回答正确！"), TEXT("结果"), MB_OK);
				}
				else
				{
					mistake++;
					snprintf(burff, 200, "回答错误！答案为%d。", factorialAnswer);
					MessageBox(hwnd, burff, TEXT("结果"), MB_OK);
				}

				//另类的出题循环方法，由于无法使用do-while循环，故用此下策
				if (i > 0)
				{
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
					hdc = GetDC(hwnd);
					factorial = generate_factorialTocip(topic);
					ILength = lstrlen(topic);
					factorialAnswer = fac(factorial);

					TextOut(hdc, 300, 120, "题目类型:       阶乘", 20);
					TextOut(hdc, 300, 150, topic, ILength);
					TextOut(hdc, 300, 210, "答案      :", 11);

					hwndInput2 = CreateWindow(TEXT("edit"), NULL,
						WS_CHILD | WS_VISIBLE | WS_BORDER |
						ES_LEFT,
						380, 210, 100, 22,
						hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

					btnHwnd2 = CreateWindow(TEXT("button"), TEXT("确认"),
						WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						350, 250,
						100, 30,
						hwnd,
						(HMENU)6,
						(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
						NULL);
				}
				else
				{
					finish = clock();
					cost = (double)(finish - start) / CLOCKS_PER_SEC;
					snprintf(burff, 200, "答题共用时：%.2f秒，答对：%d题，答错:%d题。", cost, correct, mistake);
					MessageBox(hwnd, burff, TEXT("结果"), MB_OK);
					correct = 0, mistake = 0;
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
				}
				break;
			}
			break;

		case IDM_Background://菜单中变更背景颜色按钮的点击事件
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
				if (bgcolor == 1)
				{
					SetClassLongPtr(hwnd, GCL_HBRBACKGROUND, (long)hbmp1);
					InvalidateRect(hwnd, NULL, TRUE);
					UpdateWindow(hwnd);
					bgcolor = 2;
					break;
				}
				else if (bgcolor == 2)
				{
					SetClassLongPtr(hwnd, GCL_HBRBACKGROUND, (long)hbmp2);
					InvalidateRect(hwnd, NULL, TRUE);
					UpdateWindow(hwnd);
					bgcolor = 3;
					break;
				}
				else if (bgcolor == 3)
				{
					SetClassLongPtr(hwnd, GCL_HBRBACKGROUND, (long)hbmp3);
					InvalidateRect(hwnd, NULL, TRUE);
					UpdateWindow(hwnd);
					bgcolor = 4;
					break;
				}
				else if (bgcolor == 4)
				{
					SetClassLongPtr(hwnd, GCL_HBRBACKGROUND, (long)hbmp4);
					InvalidateRect(hwnd, NULL, TRUE);
					UpdateWindow(hwnd);
					bgcolor = 5;
					break;
				}
				else if (bgcolor == 5)
				{
					SetClassLongPtr(hwnd, GCL_HBRBACKGROUND, (long)hbmp5);
					InvalidateRect(hwnd, NULL, TRUE);
					UpdateWindow(hwnd);
					bgcolor = 1;
					break;
				}
			}
			break;

		case IDM_Explain://菜单中说明按钮的点击事件
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				MessageBox(hwnd, TEXT("点击生成题目选择题型后，输入题目个数、运算符号的个数（阶乘没有运算符号个数）;\n题目个数不能为0且最大不超过5，运算符号的个数大于2但不超过4！"), TEXT("说明"), MB_OK);
				break;
			}
			break;

		case IDM_Exit://菜单中退出按钮的点击事件
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

/*
生成整数题目，第一个参数为运算字符个数，第二个参数题目字符串地址
*/
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

/*
生成分数题目，第一个参数为运算字符个数，第二个参数题目字符串地址
*/
void generate_fractionTocip(int symbolNumber, char *topic)
{
	char burff[200];
	int i, symbolRandom, random1, random2;
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

/*
生成阶乘题目，参数题目字符串地址
返回值为需要求阶乘的数
*/
int generate_factorialTocip(char *topic)
{
	char burff[200];
	int  random;

	srand((unsigned)time(NULL));
	random = rand() % 10 + 1;

	snprintf(burff, 200, "%d! = ", random);
	lstrcat(topic, burff);

	return random;
}

/*
计算阶乘的结果，参数为需要阶乘的数
返回值即为结果
*/
int fac(int n)
{
	int answer;

	if (n == 0 || n == 1)
	{
		answer = 1;
	}
	else
	{
		answer = fac(n - 1)*n;
	}

	return answer;
}

/*
清理屏幕，参数为父窗口句柄与所有子窗口句柄
*/
void clearScreen(HWND hwnd, HWND hwndInput1, HWND hwndInput2, HWND hwndInput3, HWND btnHwnd1, HWND btnHwnd2)
{
	InvalidateRect(hwnd, NULL, TRUE);
	UpdateWindow(hwnd);
	DestroyWindow(hwndInput1);
	DestroyWindow(hwndInput2);
	DestroyWindow(hwndInput3);
	DestroyWindow(btnHwnd1);
	DestroyWindow(btnHwnd2);
}