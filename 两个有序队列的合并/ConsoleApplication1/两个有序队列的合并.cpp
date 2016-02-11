/*
��Ŀ����

����������������Ķ��У������Ǻϲ���һ��������С�


 ��������

  �����������ж��顣ÿ���������У�ÿһ�б�ʾһ��������У����е�Ԫ��Ϊ������������Ϊ0ʱ(0�����ڸö���)��ʾ���н�����
	���������о�Ϊ�ն���ʱ�����������


�������

	���ϲ�֮��Ķ����е�Ԫ�ذ��������ÿ��Ԫ����һ���ո��������β�����ж���Ŀո�


��������

	1 3 4 6 8 0
	2 3 5 9 11 12 0
	0
	0


�������

	1 2 3 3 4 5 6 8 9 11 12
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct QNode //����Ľṹ�� 
{
	int data;
	struct QNode * next;
}QNode, *QueuePtr;


typedef struct //���еĽṹ��
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
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));//����һ���µ�����ڵ�p
	QueuePtr q = (QueuePtr)malloc(sizeof(QNode));//�����һ���ڵ�p֮���ٷ�һ���ڵ����ѭ��
	p->data = num;//��Ҫ�����num�ŵ��ڵ�p��data��
	p->next = q;//��ֹp��ָ����Ϊ��ʱ�˳�ѭ������ɵ�����
	q->next = NULL;//q��ָ����Ϊ�� ��Ϊ���һ���ڵ�
	Q->rear->next = p;//���еĶ�βָ������ָ��p��ǰһ���ڵ� ������ڵ��nextָ��p ��ô���ھͰ�p�ڵ�ҵ��˶�����
	Q->rear = p;//�ö�βָ��ָ��p ʹp��Ϊ��β
}

void MergeQueue(LinkQueue * Q1, LinkQueue * Q2, LinkQueue * Q)
{
	//��q1 <= q2 q = q1
	//��q1 > q2 q = q2
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
	LinkQueue Q1;//����1
	LinkQueue Q2;//����2
	LinkQueue Q;//�ϲ���Ķ���
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