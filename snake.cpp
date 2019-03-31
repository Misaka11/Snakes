
#include "stdafx.h"
#include "snake.h"

BYTE g_World[WIDTH][HEIGHT] = {0}; //游戏界面
//0 表示通路  1 表示蛇的身体  2 表示苹果 

short dx[4] = {0,0,-1,1},
	  dy[4] = {-1,1,0,0};	//方向数组

//球的函数定义
void Snake::Ball:: DrawBall(int x,int y)
	{
		setfillcolor(BLUE);
		setlinecolor(BLUE);
		circle(x * UNIT + 5,y * UNIT + 5, 3);
		solidcircle(x * UNIT + 5,y * UNIT + 5, 3);
	}
void Snake::Ball::NewBall()
	{
		do
		{
			x = rand() % WIDTH;
			y = rand () % HEIGHT;
		}while(g_World[x][y] != 0);
		g_World[x][y] = 2;
		DrawBall(x,y);
	}


/*********************************/


//蛇的函数定义
void Snake::Draw(CD *t,COLORREF color)	
	{
		setlinecolor(color);
		setfillcolor(color);
		circle(t->x * UNIT + 5,t->y * UNIT + 5, 4);
		solidcircle(t->x * UNIT + 5,t->y * UNIT + 5, 4);	
	}
ST	Snake::Judge()
	{
		if(head->x > WIDTH - 1 || head->x < 0 || head->y > HEIGHT - 1 || head->y < 0) return DIE; //撞到墙
		if(g_World[head->x][head->y] == 1 ) return DIE;			//撞到自己
		if(g_World[head->x][head->y] == 2) return EAT;
		return OK;
	}

void Snake::Reset(unsigned int le)
	{
		level = le;
		live = 1;
		head = new CD;
		head->x = 5;
		head->y = 5;
		dir = RIGHT;
		tail = new CD;
		tail->x = 4;
		tail->y = 5;
		tail->next = head;
		bhead = tail;		//正式建立起蛇身
		Draw(head,YELLOW);
		Draw(tail,RED);
		Lock(head);
		Lock(tail);
		apple.NewBall();
	}
void Snake::Move(DIR d)
	{
		switch(d)						//此处有一个优化的想法 if（｜dir - d｜ = 2） dir = d; 但要改好多东西，就不改了
		{
			case UP:
				if(dir != DOWN) dir = d;	break;
			case DOWN:
				if(dir != UP)	dir = d;	break;
			case LEFT:
				if(dir != RIGHT)dir = d;	break;
			case RIGHT:
				if(dir != LEFT)	dir = d;
		}
		CD *newbody = new CD;
		newbody->x = head->x + dx[dir];
		newbody->y = head->y + dy[dir];
		head->next = newbody;
		head = newbody;
		bhead = bhead->next;
		
		CD *t;
		switch(Judge())
		{
			case DIE: 
				Die();
				break;
			case OK:
				t = tail;
				Draw(head,YELLOW);
				Draw(bhead,RED);
				Draw(tail,BLACK);
				UnLock(tail);
				tail = tail->next;
				free(t);
				Lock(head);
				break;
			case EAT: ;
				Lock(head);
				apple.NewBall();
				Draw(head,YELLOW);
				Draw(bhead,RED);
				Draw(tail,BLACK);
		}	

	}
void Snake::Die()
	{	
		CD *t;
		for(int i = 0; i < 3; i++ )
		{
			Sleep(500);
			t = tail;
			while(t != head) {Draw(t, DARKGRAY);t = t->next;}
			Sleep(500);
			t = tail;
			while(t != head)  {Draw(t, WHITE);t = t->next;}
		}
		while(tail != head)
		{
			t = tail;
			tail = tail->next;
			free(t);
		}
		free(tail);
		live = 0;
	}
DIR Snake::GetDir()
	{
		DWORD old_time = GetTickCount();
		while (1)
		{
			
			DWORD  new_time = GetTickCount();
			if(new_time - old_time >=level * 50)
			{
				old_time = new_time;
				return dir;
			}
			
			if(kbhit())
				switch(getch())
				{
					case 0:
					case 0xE0:
						switch(getch())
						{
							case 72: return UP;
							case 75: return LEFT;
							case 77: return RIGHT;
							case 80: return DOWN;
						}
		
				}
			Sleep(50);
		}
		return KEEP;
	}
void Snake::Lock(CD *t){g_World[t->x][t->y]=1;}
void Snake::UnLock(CD *t){g_World[t->x][t->y]=0;}
