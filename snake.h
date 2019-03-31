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
enum ST		//�����ж�3��״̬
{
	DIE,EAT,OK	//�������Ե�ƻ����һ������
};

typedef struct coordinate
{
	WORD x,y;
	coordinate *next; 
} CD;



/***********
��
**************/
class Snake
{
private:
//	DWORD len;											//������
	CD* head;											//��ͷ����
	CD* tail;											//��β����
	CD* bhead;
	DIR dir;											//��ͷ����
	bool live;											//���Ƿ���
	unsigned int level;									//�趨�Ѷ�
														//���Ὠ����������������βΪ��ͷ
	void Draw(CD *, COLORREF);						//����λ����
	void Lock(CD *t);
	void UnLock(CD *t);
	ST Judge();
public:
//	DWORD Length() {return len;}
	bool Live()	{return live;}
	void Reset(unsigned int);										//����
	void Move(DIR d);									//�ƶ�
	void Die();											//����
	DIR GetDir();											//��ȡ���߷���


	/*************
	ƻ��  �ں���
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