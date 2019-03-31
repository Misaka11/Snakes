#ifndef SNAKE
#define SNAKE

#include "stdafx.h"

#define WIDTH 40
#define HEIGHT 40
#define UNIT 10


enum DIR
{
	UP,DOWN,LEFT,RIGHT,KEEP
};
enum ST		//用于判断3种状态
{
	DIE,EAT,OK	//死亡，吃到苹果，一切正常
};

typedef struct coordinate
{
	WORD x,y;
	coordinate *next; 
} CD;



/***********
蛇
**************/
class Snake
{
private:
//	DWORD len;											//蛇身长度
	CD* head;											//蛇头坐标
	CD* tail;											//蛇尾坐标
	CD* bhead;
	DIR dir;											//蛇头方向
	bool live;											//蛇是否存活
	unsigned int level;									//设定难度
														//待会建立起来的链表以蛇尾为表头
	void Draw(CD *, COLORREF);						//画单位身体
	void Lock(CD *t);
	void UnLock(CD *t);
	ST Judge();
public:
//	DWORD Length() {return len;}
	bool Live()	{return live;}
	void Reset(unsigned int);										//重置
	void Move(DIR d);									//移动
	void Die();											//死亡
	DIR GetDir();											//获取行走方向


	/*************
	苹果  内含类
	***************/
	class Ball
	{
	private:
		int x,y;
		void DrawBall(int x,int y);
	public:
		void NewBall();
	}apple;
};
#endif