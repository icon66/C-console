
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

//������ǰ
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

//�������
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


//��ת
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

//��ת
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

//����
void CLogo::Hide()
{
	ShowStatus = false;
}

//��ʾ
void CLogo::Show()
{
	ShowStatus = true;
}

//���»��ʣ���ʾ�˶��켣
void CLogo::PenDown()
{
	Position.isShow = true;
}

//̧�𣬲�ʾ�˶��켣
void CLogo::PenUp()
{
	Position.isShow = false;
}

//����������ص�ԭ��λ��
void CLogo::Clear()
{
	Position.x = 200;
	Position.y = 200;
	//�������
	vecPatch.clear();
	vecPatch.push_back(Position);
	ShowStatus = true;
	Angle = 0;
	CalcuPosition();
}

//���ݻ���λ�ü�������������λ��
void CLogo::CalcuPosition()
{
	Position1.x = Position.x + cos((-Angle) / 180 * PI) * Radius;
	Position1.y = Position.y + sin((-Angle) / 180 * PI) * Radius;
	Position2.x = Position.x + cos((-Angle +120) / 180 * PI) * Radius;
	Position2.y = Position.y + sin((-Angle +120) / 180 * PI) * Radius;
	Position3.x = Position.x + cos((-Angle +240) / 180 * PI) * Radius;
	Position3.y = Position.y + sin((-Angle +240) / 180 * PI) * Radius;
}

//���ݺ����������������㣬�滭����������
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

//��������˶��켣
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

//����
void CLogo::Draw()
{
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();
	DrawLogo();
	DrawImprint();
	FlushBatchDraw();
}

//�û������
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

//ִ������
void CLogo::Reapet(char* cmd)
{
	CStack S;								// �����ַ�ƥ��
	int SIZE = 200;							//ջ�Ĵ�С	
	char* ptr = nullptr, * ptr1 = nullptr;	//ָ�� �����е�ָ��
	char* ch = nullptr;						//���ڿ���������()�ڵ�����
	int i = 0, j = 0, k = 0, count = 0;		//ѭ��������

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
					delete[]ch;	//�ͷ��ڴ�
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
			//		delete[]ch;	//�ͷ��ڴ�
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
	S.DestroyStack();	//����ջ
}

//��ȡ�ַ���������ȡ�����ַ���ת��������
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



