// 贪吃蛇.cpp : 定义控制台应用程序的入口点。
//
/******************
作者：11
开始日期：2017.2.26
定稿时期：2017.2.28
*******************/

#include "stdafx.h"
#include "snake.h"

Snake player;	//创建游戏者
//函数
extern BYTE g_World[WIDTH][HEIGHT];

void init();
void NewGame();

int _tmain(int argc, _TCHAR* argv[])
{
	init();
	int over = 0;
	HWND wnd;
	while(!over)
	{
		wnd = GetHWnd();
		if(MessageBox(wnd,_T("Do you want to play now?"),_T("New Game"),MB_YESNO | MB_ICONQUESTION) == IDYES)
			NewGame();
		else over = 1;
		setfillcolor(BLACK);
		solidrectangle(1,1,399,399);
	}
	closegraph();
	return 0;
}

void init()
{
	initgraph(640,480);
	setbkmode(TRANSPARENT);
	settextstyle(14,0,_T("宋体"));
	outtextxy(20,460,_T("上：↑"));
	outtextxy(70,460,_T("左：←"));
	outtextxy(120,460,_T("右：→"));
	outtextxy(170,460,_T("下：↓"));
	outtextxy(230,460,_T("提示：按住方向键可加速"));
	srand((unsigned)time(0));
	setorigin(20,20);
	/******
	战榜模式待添加
	*********/
}

void NewGame()
{
	ZeroMemory(g_World, WIDTH * HEIGHT);
	char a[5];
	InputBox((LPTSTR)a,5,_T("please choose level: 1 - hard ,2,3,...9 -easy") );
	unsigned int t;
	t = atoi(a);
	player.Reset(t);
	setlinecolor(WHITE);
	rectangle(0,0,400,400);
	while(player.Live())
	{
		DIR d = player.GetDir();
		player.Move(d);
	}
	Sleep(2000);
}
