/*
题目描述

　　给出两个有序的队列，将他们合并成一个有序队列。


 输入描述

  　输入数据有多组。每组数据两行，每一行表示一个有序队列，队列的元素为正整数，输入为0时(0不属于该队列)表示队列结束。
	当两个队列均为空队列时，输入结束。


输出描述

	将合并之后的队列中的元素按序输出，每个元素用一个空格隔开，结尾不能有多余的空格。


输入样例

	1 3 4 6 8 0
	2 3 5 9 11 12 0
	0
	0


输出样例

	1 2 3 3 4 5 6 8 9 11 12
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct QNode //链表的结构体 
{
	int data;
	struct QNode * next;
}QNode, *QueuePtr;


typedef struct //队列的结构体
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void InitQueue(LinkQueue * Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	Q->front->next = NULL;
}


void EnQueue(LinkQueue * Q, int num)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));//创建一个新的链表节点p
	QueuePtr q = (QueuePtr)malloc(sizeof(QNode));//在最后一个节点p之后再放一个节点便于循环
	p->data = num;//把要插入的num放到节点p的data域
	p->next = q;//防止p的指针域为空时退出循环而造成的问题
	q->next = NULL;//q的指针域为空 成为最后一个节点
	Q->rear->next = p;//队列的队尾指针现在指向p的前一个节点 让这个节点的next指向p 那么现在就把p节点挂到了队列中
	Q->rear = p;//让队尾指针指向p 使p成为队尾
}

void MergeQueue(LinkQueue * Q1, LinkQueue * Q2, LinkQueue * Q)
{
	//当q1 <= q2 q = q1
	//当q1 > q2 q = q2
	QueuePtr q1 = Q1->front->next;
	QueuePtr q2 = Q2->front->next;

	while (q1->next != NULL && q2->next != NULL)
	{
		if (q1->data <= q2->data)
		{
			EnQueue(Q, q1->data);
			q1 = q1->next;
			
		}
		else
		{
			EnQueue(Q, q2->data);
			q2 = q2->next;
			
		}
	}

	while (q1->next != NULL)
	{
		EnQueue(Q, q1->data);
		q1 = q1->next;
		
	}

	while (q2->next != NULL)
	{
		EnQueue(Q, q2->data);
		q2 = q2->next;
		
	}
}


void Traverse(LinkQueue * Q)
{
	QueuePtr q = Q->front->next;
	while (q->next->next != NULL)
	{
		printf("%d ", q->data);
		q = q->next;
	}
	printf("%d\n", q->data);
}

int main()
{
	LinkQueue Q1;//队列1
	LinkQueue Q2;//队列2
	LinkQueue Q;//合并后的队列
	int num;

	while (1)
	{
		InitQueue(&Q1);
		InitQueue(&Q2);
		InitQueue(&Q);

		while ((scanf("%d", &num)) != EOF)
		{
			if (num == 0)
			{
				break;
			}
			EnQueue(&Q1, num);
		}

		while ((scanf("%d", &num)) != EOF)
		{
			if (num == 0)
			{
				break;
			}
			EnQueue(&Q2, num);
		}

		if (Q1.front == Q1.rear && Q2.front == Q2.rear)
		{
			break;
		}
		if (Q1.front == Q1.rear && Q2.front != Q2.rear)
		{
			Traverse(&Q2);
			break;
		}
		if (Q1.front != Q1.rear && Q2.front == Q2.rear)
		{
			Traverse(&Q1);
			break;
		}
		MergeQueue(&Q1, &Q2, &Q);
		//Traverse(&Q1);
		//Traverse(&Q2);
		Traverse(&Q);
	}

	return 0;
	
}