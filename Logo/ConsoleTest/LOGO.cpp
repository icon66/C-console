
#pragma once
#include "Logo.h"
#include "math.h"
#include "Stack.h"
#include <iostream>
using namespace std;
#define PI 3.141

CLogo::CLogo()
{
	Size = 50;
	ShowStatus = true;
	Angle = 0;
	Position.SetPoint(200, 200);
	vecPatch.push_back(Position);
	Radius = (Size / 2) / (cos(30 / 180 * PI));
	CalcuPosition();
}

CLogo::~CLogo()
{
	
}

//海龟向前
void CLogo::Forward(int steps)
{
	int count = 0;
	while (count<steps)
	{
		count++;
		if (Position.x>640)
		{
			Position.x = 0;
		}
		else if(Position.x<=0)
		{
			Position.x = 640;
		}
		else if (Position.y > 600)
		{
			Position.y = 0;
		}
		else if (Position.y <= 0)
		{
			Position.y = 600;
		}
		Position.x += cos(-Angle / 180 * PI);
		Position.y += sin(-Angle / 180 * PI);
		CalcuPosition();
		if (vecPatch.size() > 0)
		{
			if (vecPatch.back().x != Position.x || vecPatch.back().y != Position.y)
			{
				vecPatch.push_back(Position);
			}
		}
		Draw();
	}
}

//海龟后退
void CLogo::Back(int steps)
{
	int count = 0;
	while (count < steps)
	{
		count++;
		if (Position.x > 640)
		{
			Position.x = 0;
		}
		else if (Position.x <= 0)
		{
			Position.x = 640;
		}
		else if (Position.y > 600)
		{
			Position.y = 0;
		}
		else if (Position.y <= 0)
		{
			Position.y = 600;
		}
		Position.x -= cos(-Angle / 180 * PI);
		Position.y -= sin(-Angle / 180 * PI);
		CalcuPosition();
		if (vecPatch.size() > 0)
		{
			if (vecPatch.back().x != Position.x || vecPatch.back().y != Position.y)
			{
				vecPatch.push_back(Position);
			}
		}
		Draw();
	}
}


//左转
void CLogo::TurnLeft(int angle_val)
{
	int count = 0;
	while (count < angle_val)
	{
		count++;
		Angle += 1;
		CalcuPosition();
		Draw();
	}
}

//右转
void CLogo::TurnRight(int angle_val)
{
	int count = 0;
	while (count < angle_val)
	{
		count++;
		Angle -= 1;
		CalcuPosition();
		Draw();
	}
}

//隐藏
void CLogo::Hide()
{
	ShowStatus = false;
}

//显示
void CLogo::Show()
{
	ShowStatus = true;
}

//放下画笔，显示运动轨迹
void CLogo::PenDown()
{
	Position.isShow = true;
}

//抬起，不示运动轨迹
void CLogo::PenUp()
{
	Position.isShow = false;
}

//清屏，海龟回到原点位置
void CLogo::Clear()
{
	Position.x = 200;
	Position.y = 200;
	//清除容器
	vecPatch.clear();
	vecPatch.push_back(Position);
	ShowStatus = true;
	Angle = 0;
	CalcuPosition();
}

//根据画笔位置计算另三个顶点位置
void CLogo::CalcuPosition()
{
	Position1.x = Position.x + cos((-Angle) / 180 * PI) * Radius;
	Position1.y = Position.y + sin((-Angle) / 180 * PI) * Radius;
	Position2.x = Position.x + cos((-Angle +120) / 180 * PI) * Radius;
	Position2.y = Position.y + sin((-Angle +120) / 180 * PI) * Radius;
	Position3.x = Position.x + cos((-Angle +240) / 180 * PI) * Radius;
	Position3.y = Position.y + sin((-Angle +240) / 180 * PI) * Radius;
}

//根据海龟三角形三个顶点，绘画海龟三角形
bool CLogo::DrawLogo()
{
	if (ShowStatus)
	{
		setlinecolor(CYAN);
		line(Position1.x, Position1.y, Position2.x, Position2.y);
		line(Position1.x, Position1.y, Position3.x, Position3.y);
		setlinecolor(BLACK);
		line(Position2.x, Position2.y, Position3.x, Position3.y);
	}
	return true;
}

//画海龟的运动轨迹
void CLogo::DrawImprint()
{
	setlinecolor(RED);
	if (vecPatch.size()>1)
	{
		for (int i = 0; i < vecPatch.size()-1; i++)
		{
			if (vecPatch[i].isShow&& vecPatch[i].x>0&& vecPatch[i].y>0&&vecPatch[i].x < 600 && vecPatch[i].y < 600)
			{
				line(vecPatch[i].x, vecPatch[i].y, vecPatch[i + 1].x, vecPatch[i + 1].y);
			}
		}
	}
}

//绘制
void CLogo::Draw()
{
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();
	DrawLogo();
	DrawImprint();
	FlushBatchDraw();
}

//用户命令处理
void CLogo::Cmd(const char* cmd)
{
	char*CmdLine = new char[strlen(cmd) + 1];
	if (CmdLine)
	{
		strcpy_s(CmdLine, strlen(cmd) + 1, cmd);
		Reapet(CmdLine);
		delete[]CmdLine;
		CmdLine = NULL;
	}
}

//执行命令
void CLogo::Reapet(char* cmd)
{
	CStack S;								// 用于字符匹配
	int SIZE = 200;							//栈的大小	
	char* ptr = nullptr, * ptr1 = nullptr;	//指向 命令行的指针
	char* ch = nullptr;						//用于拷贝命令中()内的内容
	int i = 0, j = 0, k = 0, count = 0;		//循环计数器

	ptr = cmd;
	while (ptr != nullptr && *ptr != '\0')
	{
 		switch (*ptr)
		{
		case 'F':
			//printf("F\n");
			Forward(Atoi(ptr, k));
			ptr += k;
			break;
		case 'B':
			//printf("B\n");
			Back(Atoi(ptr, k));
			ptr += k;
			break;
		case 'T':
		{
			//printf("T\n");
			ptr++;
			switch (*ptr)
			{
			case 'L':
				//printf("L\n");
				TurnLeft(Atoi(ptr, k));
				ptr += k;
				break;
			case 'R':
				//printf("R\n");
				TurnRight(Atoi(ptr, k));
				ptr += k;
				break;
			default:break;
			}
			break;
		}
		case 'H':
			//printf("H\n");
			Hide();
			break;
		case 'S':
			//printf("S\n");
			Show();
			break;
		case 'C':
			//printf("C\n");
			Clear();
			break;
		case 'P':
		{
			//printf("P\n");
			ptr++;
			switch (*ptr)
			{
			case 'U':
				//printf("U\n");
				PenUp();
				break;
			case 'D':
				//printf("D\n");
				PenDown();
				break;
			default:break;
			}
			break;
		}
		case 'R':
		{
			//printf("R\n");
			S.InitStack(SIZE);
			count = Atoi(ptr, k);
			ptr += k;
			int times = 0;
			while (times<count)
			{
				times++;
				ptr1 = ptr;
				j = 0;
				ch = new char[SIZE];
				if (!ch)
					break;
				while (*ptr1 != '\0' && ptr1 != nullptr && j < SIZE)
				{
					ch[j++] = *ptr1;
					if (*ptr1 == '(')
						S.Push(*ptr);
					if (*ptr1 == ')')
					{
						S.Pop();
						if (S.IsEmpty())
						{
							ch[j] = '\0';
							Reapet(ch);
							break;
						}
					}
					ptr1++;
				}
				if (ch)
					delete[]ch;	//释放内存
				ch = nullptr;
			}
			//for (i = 0; i < count; i++)
			//{
			//	ptr1 = ptr;
			//	j = 0;
			//	ch = new char[SIZE];
			//	if (!ch)
			//		break;
			//	while (*ptr1 != '\0' && ptr1 != nullptr && j < SIZE)
			//	{
			//		ch[j++] = *ptr1;
			//		if (*ptr1 == '(')
			//			S.Push(*ptr);
			//		if (*ptr1 == ')')
			//		{
			//			S.Pop();
			//			if (S.IsEmpty())
			//			{
			//				ch[j] = '\0';
			//				Reapet(ch);
			//				break;
			//			}
			//		}
			//		ptr1++;
			//	}
			//	if (ch)
			//		delete[]ch;	//释放内存
			//	ch = nullptr;
			//}
			ptr = ptr1;
			break;
		}
		default:
			break;
		}
		if (ptr == NULL)
			break;
		ptr++;
	}
	S.DestroyStack();	//销毁栈
}

//读取字符串，将读取到的字符串转换成整数
long int CLogo::Atoi(char* ptr, int& count)
{
	int ReturnInt = 0;
	int size = 10;
	count = 0;
	char ch[10];

	ptr += 2;

	while ((*ptr != ' ') && (*ptr != '(') && (*ptr != ')') && (*ptr != '\0') && (count < size - 1))
	{
		ch[count++] = *ptr++;
	}
	ch[count] = '\0';
	ReturnInt = atoi(ch);
	//cout << ReturnInt << endl;
	return ReturnInt;
}



