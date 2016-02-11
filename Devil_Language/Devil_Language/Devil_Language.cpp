#define STACK_INIT_SIZE 100
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct//字符栈
{
	char * base;
	char * top;
	int stacksize;
}SqStack;

typedef struct QNode //链表的结构体 
{
	char ch;
	struct QNode * next;
}QNode, *QueuePtr;


typedef struct //队列的结构体
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void InitStack(SqStack * S)//一个空的字符栈
{
	S->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
}


void InitQueue(LinkQueue * Q)//构建一个空队列
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	Q->rear->next = NULL;//这里写Q->front->next = NULL 调试时发现问题 书上用的这种 原因还不知道
}

void DeQueue(LinkQueue * Q, char * ch)//删除队列队头元素 并用ch保存
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

void PushStack(SqStack * S, char ch)//压栈操作 将ch压入栈
{
	*S->top = ch;
	S->top++;
	//printf("%c\n", *(S->top - 1));
}

void PopStack(SqStack * S, char * ch)//出栈操作
{
	S->top--;
	*ch = *(S->top);
}

int IsStackEmpty(SqStack * S)//判断栈是否为空的函数
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

int IsQueueEmpty(LinkQueue * Q)//判断队列是否为空的函数
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

void EnQueue(LinkQueue * Q, char ch)//进队操作
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	p->ch = ch;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
}

void toChineseQueue(LinkQueue * Q)//将转化后的魔王语言转换成中文并输出
{
	char ch;
	while (IsQueueEmpty(Q))
	{
		DeQueue(Q, &ch);
		switch (ch)
		{
		case 't':
			printf("天");
			break;

		case 'd':
			printf("地");
			break;

		case 's':
			printf("上");
			break;

		case 'a':
			printf("一只");
			break;

		case 'e':
			printf("鹅");
			break;

		case 'z':
			printf("追");
			break;

		case 'g':
			printf("赶");
			break;

		case 'x':
			printf("下");
			break;

		case 'n':
			printf("蛋");
			break;

		case 'h':
			printf("恨");
			break;

		case 'B':
			printf("天上一只鹅地上一只鹅");
			break;

		case 'A':
			printf("上一只鹅");
			break;

		default:
			break;
		}
	}

	printf("\n");
}

char getFront(LinkQueue * Q)//获取到队列头元素
{
	return Q->front->ch;
}

int main()
{
	char str[20];
	int i;
	int length;
	char chOut1, chOut2, e;//e为出队列的数据
	char B[] = "tsaedsae";//其实是tAdA 这里直接把A=sae替换了
	char A[] = "sae";

	LinkQueue Q;
	LinkQueue QPrint;//用来将字符转换成汉子的队列
	SqStack S1, S2;//S1为输入的魔王语言的逆序栈 S2为在括号之外的字符逆序栈

	InitStack(&S1);
	InitStack(&S2);
	InitQueue(&Q);
	InitQueue(&QPrint);

	scanf("%s", &str);
	length = strlen(str);//求出魔王语言的长度 便于控制循环

	//printf("%d\n", length);

	for (i = length - 1; i >= 0; i--)
	{
		PushStack(&S1, str[i]);
	}



	while (IsStackEmpty(&S1))
	{
		PopStack(&S1, &chOut1);
		if (chOut1 == 'B')//匹配到B就把B放到栈S2中
		{
			PushStack(&S2, chOut1);
		}

		else if (chOut1 == '(')//匹配到左括号时就把就把括号中的元素顺序放到队列Q中 直到匹配到右括号
		{
			PushStack(&S2, '#');//碰到括号先在栈2中放一个#便于标识 便于处理括号中的字符
			PopStack(&S1, &chOut1);//将魔王语言的逆序栈中的字符pop出

			while (chOut1 != ')')
			{
				EnQueue(&Q, chOut1);//进队列
				PopStack(&S1, &chOut1);
			}
			DeQueue(&Q, &chOut2);//根据规则2 将左括号后的第一个字符先出队列 并保存 用于反复操作
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
		PopStack(&S2, &chOut1);//把队尾的B pop出给chout1
		if (chOut1 != '#')
		{
			PushStack(&S1, chOut1);//再没碰到#之前把chout1压进s1
		}
		else
		{
			while (IsQueueEmpty(&Q))
			{
				DeQueue(&Q, &e);
				PushStack(&S1, chOut2);//chout2是已经取出的队头 在第151行
				PushStack(&S1, e);//将出队列的元素压入现在已经是空的栈S1
			}

			PushStack(&S1, chOut2);//根据题目要求 需要再压入一个chout2
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