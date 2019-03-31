// ̰����.cpp : �������̨Ӧ�ó������ڵ㡣
//
/******************
���ߣ�11
��ʼ���ڣ�2017.2.26
����ʱ�ڣ�2017.2.28
*******************/

#include "stdafx.h"
#include "snake.h"

Snake player;	//������Ϸ��
//����
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
	settextstyle(14,0,_T("����"));
	outtextxy(20,460,_T("�ϣ���"));
	outtextxy(70,460,_T("�󣺡�"));
	outtextxy(120,460,_T("�ң���"));
	outtextxy(170,460,_T("�£���"));
	outtextxy(230,460,_T("��ʾ����ס������ɼ���"));
	srand((unsigned)time(0));
	setorigin(20,20);
	/******
	ս��ģʽ�����
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
