#pragma once
#include <graphics.h>
#include<vector>
#include "string.h"
#include <graphics.h>
#include <string>
using namespace std;
//海龟三角形顶点结构

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
//海龟三角形类
//
class CLogo
{
public:
	CLogo();
	virtual ~CLogo();

private:
	Point	Position;							//画笔位置，位于乌龟中心
	Point	Position1, Position2, Position3;	//三个顶点位置
	int		Size;								//三角形的边长
	bool	ShowStatus;							//状态，true 显示， false 隐藏
	float	Angle;								//角度默认0，方向为x正半轴
	float	Radius;								//画笔离三个点的距离
	char*   CmdLine;							//处理用户输入的命令
	vector <Point> vecPatch;

public:
	//海龟三角形行为
	void Forward(int);						//向前				
	void Back(int);							//向后
	void TurnLeft(int);						//左转
	void TurnRight(int);					//右转
	void PenUp();							//放下画笔
	void PenDown();							//抬起画笔
	void Hide();							//隐藏
	void Show();							//显示
	void Clear();							//清屏

	bool DrawLogo();						//画海龟三角形
	void DrawImprint();						//画海龟移动痕迹
	void Draw();							//绘图		
	void CalcuPosition();					//根据海龟三角形顶点计算另两个点的位置
	void Cmd(const char*);					//用户输入的命令处理
	void Reapet(char*);						//重复命令处理
	long int Atoi(char* cmd, int& count);	//读取字符串，将字符串转换成整数
};
