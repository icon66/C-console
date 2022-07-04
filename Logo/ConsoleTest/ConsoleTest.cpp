// ConsoleTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"LOGO.h"
#include<conio.h>
#include"TextBox.h"
using namespace std;

#define PI 3.14

void initTips()
{
	settextcolor(BLACK);
	outtextxy(700, 25, L"命令样式以及键盘操作");
	outtextxy(700, 50, L"按下空格键开启键盘操作");
	outtextxy(700, 75, L"命令后接空格和数值");
	outtextxy(700, 100, _TEXT("前进1 F 1 -> ↑"));
	outtextxy(700, 125, L"后退1 B 1 -> ↓");
	outtextxy(700, 150, L"向左旋转1度 TL 1 -> ←");
	outtextxy(700, 175, L"向右旋转1度 TR 1 -> →");
	outtextxy(700, 200, L"抬起画笔 PU -> U");
	outtextxy(700, 225, L"放下画笔 PD -> D");
	outtextxy(700, 250, L"显示乌龟 H ->H");
	outtextxy(700, 275, L"隐藏乌龟 S -> S");
	outtextxy(700, 300, L"重复命令 R 次数( )");
	outtextxy(700, 325, L"画圆 R 360(F 2 TL 1)");
	outtextxy(700, 350, L"清屏 C -> C");
}

void On_btnOk_Click()
{
	return;
}

void draw(CLogo* pLogo,string s, EasyTextBox *txtInput,EasyButton *btnOK)
{
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();
	initTips();
	outtextxy(700, 380, L"输入命令：");
	btnOK->Create(740, 440, 820, 465, L"OK", On_btnOk_Click);
	string sCmd = s;
	txtInput->Create(650, 400, 950, 425, 50, sCmd);
	pLogo->DrawLogo();
	pLogo->DrawImprint();
}

int main()
{
	initgraph(1000, 600);	// 创建绘图窗口,开启输出窗口EW_SHOWCONSOLE
	CLogo* pLogo = new CLogo();
	bool isKeyControl = false;

	EasyTextBox *pTxtInput =new EasyTextBox;
	EasyButton *pBtnOK = new EasyButton;
	string sCmd = "C F 218 R 4(TR 144 F 218) TR 72 R 360(F 2 TR 1)TR 72 F 109 R 36(PU F 3 TR 5 PD F 3 TR 5)";
	draw(pLogo, sCmd, pTxtInput, pBtnOK);
	while (true)
	{
		if(GetAsyncKeyState(VK_SPACE))
		{
			isKeyControl = true;
		}
		if (isKeyControl)
		{
			if(GetAsyncKeyState(VK_UP))
			{
				pLogo->Forward(1);
			}
			else if(GetAsyncKeyState(VK_DOWN)){
				pLogo->Back(1);
			}
			else if (GetAsyncKeyState(VK_LEFT)) {
				pLogo->TurnLeft(1);
			}
			else if (GetAsyncKeyState(VK_RIGHT)) {
				pLogo->TurnRight(1);
			}
			else if (GetAsyncKeyState(VK_RIGHT)) {
				pLogo->TurnRight(1);
			}
			else if (GetAsyncKeyState('H')) {
				pLogo->Hide();
			}
			else if (GetAsyncKeyState('S')) {
				pLogo->Show();
			}
			else if (GetAsyncKeyState('D')) {
				pLogo->PenDown();
			}
			else if (GetAsyncKeyState('U')) {
				pLogo->PenUp();
			}
			else if (GetAsyncKeyState('C')) {
				pLogo->Clear();
			}
			draw(pLogo, "", pTxtInput, pBtnOK);
		}
		FlushBatchDraw();
		ExMessage msg;
		if (peekmessage(&msg,EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				// 判断控件
				if (pTxtInput->Check(msg.x, msg.y))
				{
					pTxtInput->OnMessage();
					Wchar_tToString(sCmd, pTxtInput->Text());
				}
				if (pBtnOK->Check(msg.x, msg.y))
				{
					pBtnOK->OnMessage();
					const char* cmd = sCmd.c_str();
					pLogo->Cmd(cmd);
					draw(pLogo, "", pTxtInput, pBtnOK);
				}
			default:
				break;
			}
		}
		EndBatchDraw();
	}
	return 0;
}


