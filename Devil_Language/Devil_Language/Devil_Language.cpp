#define STACK_INIT_SIZE 100
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct//�ַ�ջ
{
	char * base;
	char * top;
	int stacksize;
}SqStack;

typedef struct QNode //����Ľṹ�� 
{
	char ch;
	struct QNode * next;
}QNode, *QueuePtr;


typedef struct //���еĽṹ��
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void InitStack(SqStack * S)//һ���յ��ַ�ջ
{
	S->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
}


void InitQueue(LinkQueue * Q)//����һ���ն���
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	Q->rear->next = NULL;//����дQ->front->next = NULL ����ʱ�������� �����õ����� ԭ�򻹲�֪��
}

void DeQueue(LinkQueue * Q, char * ch)//ɾ�����ж�ͷԪ�� ����ch����
{
	QueuePtr p = Q->front->next;
	*ch = p->ch;
	Q->front->next = p->next;
	if (Q->rear == p)
	{
		Q->front = Q->rear;
	}
	free(p);
}

void PushStack(SqStack * S, char ch)//ѹջ���� ��chѹ��ջ
{
	*S->top = ch;
	S->top++;
	//printf("%c\n", *(S->top - 1));
}

void PopStack(SqStack * S, char * ch)//��ջ����
{
	S->top--;
	*ch = *(S->top);
}

int IsStackEmpty(SqStack * S)//�ж�ջ�Ƿ�Ϊ�յĺ���
{
	if (S->base == S->top)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int IsQueueEmpty(LinkQueue * Q)//�ж϶����Ƿ�Ϊ�յĺ���
{
	if (Q->front == Q->rear)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void EnQueue(LinkQueue * Q, char ch)//���Ӳ���
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	p->ch = ch;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
}

void toChineseQueue(LinkQueue * Q)//��ת�����ħ������ת�������Ĳ����
{
	char ch;
	while (IsQueueEmpty(Q))
	{
		DeQueue(Q, &ch);
		switch (ch)
		{
		case 't':
			printf("��");
			break;

		case 'd':
			printf("��");
			break;

		case 's':
			printf("��");
			break;

		case 'a':
			printf("һֻ");
			break;

		case 'e':
			printf("��");
			break;

		case 'z':
			printf("׷");
			break;

		case 'g':
			printf("��");
			break;

		case 'x':
			printf("��");
			break;

		case 'n':
			printf("��");
			break;

		case 'h':
			printf("��");
			break;

		case 'B':
			printf("����һֻ�����һֻ��");
			break;

		case 'A':
			printf("��һֻ��");
			break;

		default:
			break;
		}
	}

	printf("\n");
}

char getFront(LinkQueue * Q)//��ȡ������ͷԪ��
{
	return Q->front->ch;
}

int main()
{
	char str[20];
	int i;
	int length;
	char chOut1, chOut2, e;//eΪ�����е�����
	char B[] = "tsaedsae";//��ʵ��tAdA ����ֱ�Ӱ�A=sae�滻��
	char A[] = "sae";

	LinkQueue Q;
	LinkQueue QPrint;//�������ַ�ת���ɺ��ӵĶ���
	SqStack S1, S2;//S1Ϊ�����ħ�����Ե�����ջ S2Ϊ������֮����ַ�����ջ

	InitStack(&S1);
	InitStack(&S2);
	InitQueue(&Q);
	InitQueue(&QPrint);

	scanf("%s", &str);
	length = strlen(str);//���ħ�����Եĳ��� ���ڿ���ѭ��

	//printf("%d\n", length);

	for (i = length - 1; i >= 0; i--)
	{
		PushStack(&S1, str[i]);
	}



	while (IsStackEmpty(&S1))
	{
		PopStack(&S1, &chOut1);
		if (chOut1 == 'B')//ƥ�䵽B�Ͱ�B�ŵ�ջS2��
		{
			PushStack(&S2, chOut1);
		}

		else if (chOut1 == '(')//ƥ�䵽������ʱ�ͰѾͰ������е�Ԫ��˳��ŵ�����Q�� ֱ��ƥ�䵽������
		{
			PushStack(&S2, '#');//������������ջ2�з�һ��#���ڱ�ʶ ���ڴ��������е��ַ�
			PopStack(&S1, &chOut1);//��ħ�����Ե�����ջ�е��ַ�pop��

			while (chOut1 != ')')
			{
				EnQueue(&Q, chOut1);//������
				PopStack(&S1, &chOut1);
			}
			DeQueue(&Q, &chOut2);//���ݹ���2 �������ź�ĵ�һ���ַ��ȳ����� ������ ���ڷ�������
			//PopStack(&S1, &chOut1);
		}
		else
		{
			PushStack(&S2, chOut1);
		}
	}

	/*chOut2 = getFront(&Q);*/

	while (IsStackEmpty(&S2))
	{
		PopStack(&S2, &chOut1);//�Ѷ�β��B pop����chout1
		if (chOut1 != '#')
		{
			PushStack(&S1, chOut1);//��û����#֮ǰ��chout1ѹ��s1
		}
		else
		{
			while (IsQueueEmpty(&Q))
			{
				DeQueue(&Q, &e);
				PushStack(&S1, chOut2);//chout2���Ѿ�ȡ���Ķ�ͷ �ڵ�151��
				PushStack(&S1, e);//�������е�Ԫ��ѹ�������Ѿ��ǿյ�ջS1
			}

			PushStack(&S1, chOut2);//������ĿҪ�� ��Ҫ��ѹ��һ��chout2
		}


	}



	while (IsStackEmpty(&S1))
	{
		PopStack(&S1, &chOut1);
		EnQueue(&QPrint, chOut1);

		if (chOut1 == 'B')
		{
			printf("%s", B);
		}

		else if (chOut1 == 'A')
		{
			printf("%s", A);
		}

		else
		{
			printf("%c", chOut1);
		}
	}

	printf("\n");
	toChineseQueue(&QPrint);

	return 0;
}