#pragma once
#include <graphics.h>
#include<vector>
#include "string.h"
#include <graphics.h>
#include <string>
using namespace std;
//���������ζ���ṹ

struct Point
{
	float x, y;
	bool isShow = true;
	void SetPoint(float x_var, float y_var)
	{
		x = x_var;
		y = y_var;
	}
};

//
//������������
//
class CLogo
{
public:
	CLogo();
	virtual ~CLogo();

private:
	Point	Position;							//����λ�ã�λ���ڹ�����
	Point	Position1, Position2, Position3;	//��������λ��
	int		Size;								//�����εı߳�
	bool	ShowStatus;							//״̬��true ��ʾ�� false ����
	float	Angle;								//�Ƕ�Ĭ��0������Ϊx������
	float	Radius;								//������������ľ���
	char*   CmdLine;							//�����û����������
	vector <Point> vecPatch;

public:
	//������������Ϊ
	void Forward(int);						//��ǰ				
	void Back(int);							//���
	void TurnLeft(int);						//��ת
	void TurnRight(int);					//��ת
	void PenUp();							//���»���
	void PenDown();							//̧�𻭱�
	void Hide();							//����
	void Show();							//��ʾ
	void Clear();							//����

	bool DrawLogo();						//������������
	void DrawImprint();						//�������ƶ��ۼ�
	void Draw();							//��ͼ		
	void CalcuPosition();					//���ݺ��������ζ���������������λ��
	void Cmd(const char*);					//�û�����������
	void Reapet(char*);						//�ظ������
	long int Atoi(char* cmd, int& count);	//��ȡ�ַ��������ַ���ת��������
};
