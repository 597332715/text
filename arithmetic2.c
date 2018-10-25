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
		MessageBox(NULL, TEXT("�޷�ע�ᴰ����!"), szAppName, MB_OK | MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("��������"),
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

	HBRUSH hbmp1 = (HBRUSH)GetStockObject(LTGRAY_BRUSH);//������ɫLTGRAY
	HBRUSH hbmp2 = (HBRUSH)GetStockObject(GRAY_BRUSH);//������ɫGRAY
	HBRUSH hbmp3 = (HBRUSH)GetStockObject(DKGRAY_BRUSH);//������ɫDKGRAY
	HBRUSH hbmp4 = (HBRUSH)GetStockObject(BLACK_BRUSH);//������ɫBLACK
	HBRUSH hbmp5 = (HBRUSH)GetStockObject(WHITE_BRUSH);//������ɫWHITE

	switch (message)
	{
	case WM_COMMAND:
		hMenu = GetMenu(hwnd);

		switch (LOWORD(wParam))
		{
		case IDM_Integer://������ť�ĵ���¼�
			clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
			hdc = GetDC(hwnd);

			TextOut(hdc, 300, 150, "��Ŀ����:       ����", 20);
			TextOut(hdc, 300, 180, "��Ŀ   ����:", 12);
			TextOut(hdc, 300, 210, "���������:", 11);

			//�༭�Ӵ��ڣ����ڽ����û��������Ŀ����
			hwndInput1 = CreateWindow(TEXT("edit"), NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER |
				ES_LEFT | ES_NUMBER,
				400, 180, 25, 22,
				hwnd, (HMENU)1, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
			//�༭�Ӵ��ڣ����ڽ����û���������������
			hwndInput2 = CreateWindow(TEXT("edit"), NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER |
				ES_LEFT | ES_NUMBER,
				400, 210, 25, 22,
				hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
			//��ť�Ӵ��ڣ�����ȷ���û�������Ŀ���������������
			btnHwnd1 = CreateWindow(TEXT("button"), TEXT("ȷ��"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				310, 250,
				100, 30,
				hwnd,
				(HMENU)1,
				(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
				NULL);
			break;

		case 1://��ť����¼�������ȷ���û�������Ŀ���������������
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

					TextOut(hdc, 300, 120, "��Ŀ����:       ����", 20);
					TextOut(hdc, 300, 150, topic, ILength);
					TextOut(hdc, 300, 210, "��      :", 11);

					//�༭�Ӵ��ڣ����ڽ����û�����Ĵ�
					hwndInput3 = CreateWindow(TEXT("edit"), NULL,
						WS_CHILD | WS_VISIBLE | WS_BORDER |
						ES_LEFT,
						380, 210, 100, 22,
						hwnd, (HMENU)3, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
					//��ť�Ӵ��ڣ�����ȷ���û�����Ĵ�
					btnHwnd2 = CreateWindow(TEXT("button"), TEXT("ȷ��"),
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
					MessageBox(hwnd, TEXT("������������������������룡"), TEXT("��ʾ"), MB_OK);
				}
				break;
			}
			break;

		case 2://��ť����¼�������ȷ���û�����Ĵ�
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetWindowText(hwndInput3, Buffer, 100);
				answer = atof(Buffer);
				i--;
				MessageBox(hwnd, TEXT("�ܱ�Ǹ����δʵ��"), TEXT("��ʾ"), MB_OK);
				/*if (answer == userAnswer)
				{
					MessageBox(hwnd, TEXT("�ش���ȷ��"), TEXT("���"), MB_OK);
				}
				else
				{
					 MessageBox(hwnd, TEXT("�ش����"), TEXT("���"), MB_OK);
				}*/

				//����ĳ���ѭ�������������޷�ʹ��do-whileѭ�������ô��²�
				if (i > 0)
				{
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
					hdc = GetDC(hwnd);
					generate_integerTocip(symbolNumber, topic);
					ILength = lstrlen(topic);

					TextOut(hdc, 300, 120, "��Ŀ����:       ����", 20);
					TextOut(hdc, 300, 150, topic, ILength);
					TextOut(hdc, 300, 210, "��      :", 11);

					hwndInput3 = CreateWindow(TEXT("edit"), NULL,
						WS_CHILD | WS_VISIBLE | WS_BORDER |
						ES_LEFT,
						380, 210, 100, 22,
						hwnd, (HMENU)3, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

					btnHwnd2 = CreateWindow(TEXT("button"), TEXT("ȷ��"),
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
					MessageBox(hwnd, TEXT("�ش���ϣ�"), TEXT("���"), MB_OK);
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
				}
				break;
			}
			break;

		case IDM_Fraction://������ť�ĵ���¼�
			clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
			hdc = GetDC(hwnd);

			TextOut(hdc, 300, 150, "��Ŀ����:       ����", 20);
			TextOut(hdc, 300, 180, "��Ŀ   ����:", 12);
			TextOut(hdc, 300, 210, "���������:", 11);

			//�༭�Ӵ��ڣ����ڽ����û��������Ŀ����
			hwndInput1 = CreateWindow(TEXT("edit"), NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER |
				ES_LEFT | ES_NUMBER,
				400, 180, 25, 22,
				hwnd, (HMENU)1, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

			//�༭�Ӵ��ڣ����ڽ����û���������������
			hwndInput2 = CreateWindow(TEXT("edit"), NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER |
				ES_LEFT | ES_NUMBER,
				400, 210, 25, 22,
				hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
			//��ť�Ӵ��ڣ�����ȷ���û��������Ŀ���������������
			btnHwnd1 = CreateWindow(TEXT("button"), TEXT("ȷ��"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				310, 250,
				100, 30,
				hwnd,
				(HMENU)3,
				(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
				NULL);
			break;

		case 3://��ť����¼�������ȷ���û��������Ŀ�����������������
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

					TextOut(hdc, 300, 120, "��Ŀ����:       ����", 20);
					TextOut(hdc, 300, 150, topic, ILength);
					TextOut(hdc, 300, 210, "��      :", 11);

					//�༭�Ӵ��ڣ����ڽ����û�����Ĵ�
					hwndInput3 = CreateWindow(TEXT("edit"), NULL,
						WS_CHILD | WS_VISIBLE | WS_BORDER |
						ES_LEFT,
						380, 210, 100, 22,
						hwnd, (HMENU)3, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
					//��ť�Ӵ��ڣ�����ȷ���û�����Ĵ�
					btnHwnd2 = CreateWindow(TEXT("button"), TEXT("ȷ��"),
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
					MessageBox(hwnd, TEXT("������������������������룡"), TEXT("��ʾ"), MB_OK);
				}
				break;
			}
			break;

		case 4://��ť����¼�������ȷ���û�����Ĵ�
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetWindowText(hwndInput3, Buffer, 100);
				answer = atof(Buffer);
				i--;
				MessageBox(hwnd, TEXT("�ܱ�Ǹ����δʵ��"), TEXT("��ʾ"), MB_OK);
				/*if (answer == userAnswer)
				  {
					  MessageBox(hwnd, TEXT("�ش���ȷ��"), TEXT("���"), MB_OK);
				  }
				  else
				  {
					  MessageBox(hwnd, TEXT("�ش����"), TEXT("���"), MB_OK);
				  }*/

				  //����ĳ���ѭ�������������޷�ʹ��do-whileѭ�������ô��²�
				if (i > 0)
				{
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
					hdc = GetDC(hwnd);
					generate_fractionTocip(symbolNumber, topic);
					ILength = lstrlen(topic);

					TextOut(hdc, 300, 120, "��Ŀ����:       ����", 20);
					TextOut(hdc, 300, 150, topic, ILength);
					TextOut(hdc, 300, 210, "��      :", 11);

					hwndInput3 = CreateWindow(TEXT("edit"), NULL,
						WS_CHILD | WS_VISIBLE | WS_BORDER |
						ES_LEFT,
						380, 210, 100, 22,
						hwnd, (HMENU)3, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

					btnHwnd2 = CreateWindow(TEXT("button"), TEXT("ȷ��"),
						WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						350, 250,
						100, 30,
						hwnd,
						(HMENU)4,
						(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
						NULL);
				}
				else {
					MessageBox(hwnd, TEXT("�ش���ϣ�"), TEXT("���"), MB_OK);
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
				}
				break;
			}
			break;

		case IDM_Factorial://�׳˰�ť�ĵ���¼�
			clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
			hdc = GetDC(hwnd);

			TextOut(hdc, 300, 150, "��Ŀ����:       �׳�", 20);
			TextOut(hdc, 300, 180, "��Ŀ   ����:", 12);

			//�༭�Ӵ��ڣ����ڽ����û��������Ŀ����
			hwndInput1 = CreateWindow(TEXT("edit"), NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER |
				ES_LEFT | ES_NUMBER,
				400, 180, 25, 22,
				hwnd, (HMENU)1, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
			//��ť�Ӵ��ڣ�����ȷ���û��������Ŀ����
			btnHwnd1 = CreateWindow(TEXT("button"), TEXT("ȷ��"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				310, 250,
				100, 30,
				hwnd,
				(HMENU)5,
				(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
				NULL);
			break;

		case 5://��ť����¼�������ȷ���û��������Ŀ����
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

					TextOut(hdc, 300, 120, "��Ŀ����:       �׳�", 20);
					TextOut(hdc, 300, 150, topic, ILength);
					TextOut(hdc, 300, 210, "��      :", 11);

					//�༭�Ӵ��ڣ����ڽ����û�����Ĵ�
					hwndInput2 = CreateWindow(TEXT("edit"), NULL,
						WS_CHILD | WS_VISIBLE | WS_BORDER |
						ES_LEFT,
						380, 210, 100, 22,
						hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
					//��ť�Ӵ��ڣ�����ȷ���û�����Ĵ�
					btnHwnd2 = CreateWindow(TEXT("button"), TEXT("ȷ��"),
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
					MessageBox(hwnd, TEXT("������������������������룡"), TEXT("��ʾ"), MB_OK);
				}
				break;
			}
			break;

		case 6://��ť����¼�������ȷ���û�����Ĵ�
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetWindowText(hwndInput2, Buffer, 100);
				factorialUserAnswer = atoi(Buffer);
				i--;

				//�жϴ�����
				if (factorialAnswer == factorialUserAnswer)
				{
					correct++;
					MessageBox(hwnd, TEXT("�ش���ȷ��"), TEXT("���"), MB_OK);
				}
				else
				{
					mistake++;
					snprintf(burff, 200, "�ش���󣡴�Ϊ%d��", factorialAnswer);
					MessageBox(hwnd, burff, TEXT("���"), MB_OK);
				}

				//����ĳ���ѭ�������������޷�ʹ��do-whileѭ�������ô��²�
				if (i > 0)
				{
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
					hdc = GetDC(hwnd);
					factorial = generate_factorialTocip(topic);
					ILength = lstrlen(topic);
					factorialAnswer = fac(factorial);

					TextOut(hdc, 300, 120, "��Ŀ����:       �׳�", 20);
					TextOut(hdc, 300, 150, topic, ILength);
					TextOut(hdc, 300, 210, "��      :", 11);

					hwndInput2 = CreateWindow(TEXT("edit"), NULL,
						WS_CHILD | WS_VISIBLE | WS_BORDER |
						ES_LEFT,
						380, 210, 100, 22,
						hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

					btnHwnd2 = CreateWindow(TEXT("button"), TEXT("ȷ��"),
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
					snprintf(burff, 200, "���⹲��ʱ��%.2f�룬��ԣ�%d�⣬���:%d�⡣", cost, correct, mistake);
					MessageBox(hwnd, burff, TEXT("���"), MB_OK);
					correct = 0, mistake = 0;
					clearScreen(hwnd, hwndInput1, hwndInput2, hwndInput3, btnHwnd1, btnHwnd2);
				}
				break;
			}
			break;

		case IDM_Background://�˵��б��������ɫ��ť�ĵ���¼�
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

		case IDM_Explain://�˵���˵����ť�ĵ���¼�
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				MessageBox(hwnd, TEXT("���������Ŀѡ�����ͺ�������Ŀ������������ŵĸ������׳�û��������Ÿ�����;\n��Ŀ��������Ϊ0����󲻳���5��������ŵĸ�������2��������4��"), TEXT("˵��"), MB_OK);
				break;
			}
			break;

		case IDM_Exit://�˵����˳���ť�ĵ���¼�
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
����������Ŀ����һ������Ϊ�����ַ��������ڶ���������Ŀ�ַ�����ַ
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
���ɷ�����Ŀ����һ������Ϊ�����ַ��������ڶ���������Ŀ�ַ�����ַ
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
���ɽ׳���Ŀ��������Ŀ�ַ�����ַ
����ֵΪ��Ҫ��׳˵���
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
����׳˵Ľ��������Ϊ��Ҫ�׳˵���
����ֵ��Ϊ���
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
������Ļ������Ϊ�����ھ���������Ӵ��ھ��
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